#include "Coin.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PointLightComponent.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "TowerHop/Characters/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

ACoin::ACoin()
{
	PrimaryActorTick.bCanEverTick = true;

	// Create and assign the collider
	RootComponent = Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));

	// Create and attach the mesh
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Collider);

	// Collider defaults
	Collider->SetSphereRadius(50.f);
	Collider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Collider->SetCollisionResponseToAllChannels(ECR_Overlap);

	if (Collider)
	{
		// Bind pickup event
		Collider->OnComponentBeginOverlap.AddDynamic(this, &ACoin::OnPick);
	}

	// Create rotating movement component
	RotatingComponent = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotatingComponent"));
	RotatingComponent->RotationRate = FRotator(0.f, 180.f, 0.f);

	// Flash effect
	FlashLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("FlashLight"));
	FlashLight->SetupAttachment(RootComponent);
	FlashLight->SetVisibility(false);
}

void ACoin::OnPick(UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor || OtherActor == this) return;

	APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor);

	// Can only be picked by the player
	if (!Player) return;

	Player->PickCoin(CoinValue);

	// Make the coin disappear immediately
	Mesh->SetVisibility(false);

	if (FlashLight)
	{
		// Use the currently set intensity as max intensity of the curve
		FlashIntensity = FlashLight->Intensity;

		bFlashActive = true;
		FlashLight->SetVisibility(true);
		FlashLight->SetIntensity(0.f);

		PrimaryActorTick.SetTickFunctionEnable(true);
	}
	if (PickSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, PickSound, GetActorLocation());
	}

	// Leave a small delay for effects to happen
	SetLifeSpan(FlashDuration);
}

void ACoin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bFlashActive && FlashLight)
	{
		FlashElapsed += DeltaTime;

		float EaseDuration = FlashDuration / 2.f;
		const float EasingExponent = 2.f;

		float Alpha;
		if (FlashElapsed < FlashDuration)
		{
			// Flash is fading in
			Alpha = FMath::Clamp(FlashElapsed / EaseDuration, 0.f, 1.f);
		}
		else
		{
			// Flash reached peak intensity, now fade out
			Alpha = FMath::Clamp((FlashDuration - FlashElapsed) / EaseDuration, 0.f, 1.f);
		}
		float EasedIntensity = FMath::InterpEaseInOut(0.f, FlashIntensity, Alpha, EasingExponent);

		FlashLight->SetIntensity(EasedIntensity);

		if (FlashElapsed >= FlashDuration)
		{
			bFlashActive = false;
		}
	}
}
