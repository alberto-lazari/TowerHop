#include "Lever.h"
#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SphereComponent.h"
#include "MovingPlatform.h"
#include "TowerHop/Characters/PlayerCharacter.h"

ALever::ALever()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	Collider->SetupAttachment(RootComponent);
	Collider->SetCollisionProfileName(TEXT("BlockAllDynamic"));

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Collider);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// Create and attach the handle collider, that triggers the lever
	HandleCollider = CreateDefaultSubobject<USphereComponent>(TEXT("HandleCollider"));
	HandleCollider->SetupAttachment(Mesh);
	HandleCollider->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	HandleCollider->SetGenerateOverlapEvents(true);
	HandleCollider->OnComponentBeginOverlap.AddDynamic(this, &ALever::OnLeverActivated);
}

void ALever::OnLeverActivated(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor || OtherActor == this) return;

	// Once activated, it cannot be swicthed again
	if (bActive) return;

	if (APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor))
	{
		// Toggle lever status
		bActive = !bActive;
		Mesh->PlayAnimation(ActivateAnimation, false);

		// Activate the controlled platform
		if (ControlledPlatform)
		{
			ControlledPlatform->bActive = bActive;
		}

		// Player bounce
		FVector BounceVelocity = FVector::UpVector * HitBounceSpeed;
		Player->LaunchCharacter(BounceVelocity, true, true);
	}
}
