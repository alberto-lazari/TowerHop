#include "MovingPlatform.h"
#include "Components/StaticMeshComponent.h"

AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
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
