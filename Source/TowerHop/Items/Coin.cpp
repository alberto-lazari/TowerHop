#include "Coin.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "TowerHop/Characters/PlayerCharacter.h"

ACoin::ACoin()
{
	// Create and assign the collider
	Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	RootComponent = Collider;

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
}

void ACoin::OnPick(UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor || OtherActor == this) return;

	if (APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor))
	{
		Player->PickCoin(CoinValue);
	}

	Destroy();
}
