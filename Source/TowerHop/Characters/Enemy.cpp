#include "Enemy.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Animation/AnimSingleNodeInstance.h"

AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	if (UCapsuleComponent* Collider = GetCapsuleComponent())
	{
		// Bind hit event
		Collider->OnComponentHit.AddDynamic(this, &AEnemy::OnBodyHit);
	}

	// Create and attach head collider
	HeadCollider = CreateDefaultSubobject<USphereComponent>(TEXT("HeadCollider"));
	HeadCollider->SetupAttachment(GetMesh());
	HeadCollider->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	HeadCollider->SetGenerateOverlapEvents(true);
	HeadCollider->ComponentTags.Add(FName("Head"));
	HeadCollider->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnHeadOverlap);
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;

	PatrolRadius = GetActorLocation() - PatrolCenter;
	// Convert linear -> angular speed for the circular patrol
	PatrolSpeed = Speed / PatrolRadius.Size();
}

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsAnimating) PlayScaleAnimation(DeltaTime);
	// Stop patroling when dead
	else if (Health > 0) CircularPatrol(DeltaTime);
}

void AEnemy::OnBodyHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!OtherActor || OtherActor == this) return;

	if (APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor))
	{
		// Player takes damage
		UGameplayStatics::ApplyDamage(Player, 1.f, GetController(), this, nullptr);

		// Player bounce
		FVector KnockbackDirection = (Player->GetActorLocation() - GetActorLocation()).GetSafeNormal2D();
		Player->LaunchCharacter(HitBounceSpeed * KnockbackDirection, true, true);
	}
}

void AEnemy::OnHeadOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor || OtherActor == this) return;

	if (APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor))
	{
		// Enemy takes damage
		UGameplayStatics::ApplyDamage(this, 1.f, Player->GetController(), Player, nullptr);

		// Player bounce
		FVector BounceVelocity = FVector::UpVector * HitBounceSpeed;
		Player->LaunchCharacter(BounceVelocity, true, true);
	}
}

float AEnemy::TakeDamage(float DamageAmount, const FDamageEvent& DamageEvent,
		AController* EventInstigator, AActor* DamageCauser)
{
	// If already dead do nothing
	if (Health <= 0)
	{
		return 0.f;
	}

	Health = FMath::Max(0, Health - static_cast<int32>(DamageAmount));

	if (Health > 0)
	{
		// Play squish animation
		StartScaleAnimation(SquishedScale, CrushDuration, true);
	}
	else
	{
		Die();
	}

	return DamageAmount;
}

void AEnemy::Die()
{
	GetCharacterMovement()->DisableMovement();
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// Start crushing animation
	StartScaleAnimation(CrushedScale, CrushDuration);

	// Destroy enemy after animation
	SetLifeSpan(CrushDuration + DestroyDelay);
}

void AEnemy::StartScaleAnimation(FVector TargetScale, float Duration, bool bRestore)
{
	bIsAnimating = true;
	bRestoreAfterAnimation = bRestore;
	InitialLocation = GetActorLocation();
	InitialScale = GetActorScale3D();
	this->TargetScale = InitialScale * TargetScale;
	CapsuleHalfHeight = GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
	AnimationTimer = 0.f;
	// Duration is the total time required to play the animation and restore it
	AnimationDuration = bRestore ? Duration : Duration / 2.f;

	// Stop looping animation while the scale animation is playing
	if (UAnimSingleNodeInstance* Animation = Cast<UAnimSingleNodeInstance>(GetMesh()->GetAnimInstance()))
	{
		Animation->SetPlaying(false);
	}
}

void AEnemy::PlayScaleAnimation(float DeltaTime)
{
	// Update scale to crush vertically
	AnimationTimer += DeltaTime;
	float Alpha = AnimationTimer / AnimationDuration;
	FVector NewScale = FMath::Lerp(InitialScale, TargetScale, FMath::Clamp(Alpha, 0.f, 1.f));
	SetActorScale3D(NewScale);

	// Adjust position, since pivot is on the center
	FVector NewLocation = InitialLocation;
	float HeightDiff = (InitialScale.Z - NewScale.Z) * CapsuleHalfHeight;
	NewLocation.Z -= HeightDiff / 2.f;
	SetActorLocation(NewLocation);

	if (Alpha >= 1.f)
	{
		if (bRestoreAfterAnimation)
		{
			// Swap target/initial and restart animation to reverse
			AnimationTimer = 0.f;
			InitialLocation = GetActorLocation();
			FVector Temp = InitialScale;
			InitialScale = TargetScale;
			TargetScale = Temp;
			bRestoreAfterAnimation = false;
		}
		else
		{
			bIsAnimating = false;

			// Resume the looping animation (if not dead)
			if (UAnimSingleNodeInstance* Animation = Cast<UAnimSingleNodeInstance>(GetMesh()->GetAnimInstance()))
			{
				Animation->SetPlaying(Health > 0);
			}
		}
	}
}

void AEnemy::CircularPatrol(float DeltaTime)
{
	float AngleDelta = DeltaTime * PatrolSpeed;
	PatrolRadius = FQuat(FVector::UpVector, AngleDelta)
		.RotateVector(PatrolRadius);

	FVector NewLocation = PatrolCenter + PatrolRadius;
	FVector Movement = NewLocation - GetActorLocation();
	SetActorLocation(NewLocation);

	// Enemy should face the tanget direction of the path
	if (!Movement.IsNearlyZero())
	{
		FVector TangentDirection = FVector::UpVector.Cross(PatrolRadius).GetSafeNormal();

		// A perfect tangent direction makes enemies look like they are trying very hard to follow their
		// path and ignoring the player. Pull the direction slightly outwards to fix.
		const float PullFactor = 0.1f;
		FVector OutwardsOffset = PullFactor * PatrolRadius.GetSafeNormal();

		FRotator LookRotation = (TangentDirection + OutwardsOffset).GetSafeNormal().Rotation();
		SetActorRotation(FRotator(0.f, LookRotation.Yaw, 0.f));
	}
}
