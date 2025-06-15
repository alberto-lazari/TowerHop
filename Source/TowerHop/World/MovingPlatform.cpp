#include "MovingPlatform.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	// Make it kinematic
	Collider->SetSimulatePhysics(false);
	Collider->SetMobility(EComponentMobility::Movable);
	Collider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Collider);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	TravelDuration = FVector::Dist(Origin, Destination) / TravelSpeed;
}

void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ElapsedTime += DeltaTime;
	float Alpha = FMath::InterpEaseInOut(0.f, 1.f,
			FMath::Clamp(ElapsedTime / TravelDuration, 0.f, 1.f),
			EaseExponent);

	FVector InterpLocation = FMath::Lerp(Origin, Destination, Alpha);
	SetActorLocation(InterpLocation);

	if (ElapsedTime >= TravelDuration)
	{
		// Invert travel direction
		Swap(Origin, Destination);
		ElapsedTime = 0.f;
	}
}
