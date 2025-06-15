#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatform.generated.h"

UCLASS()
class TOWERHOP_API AMovingPlatform : public AActor
{
	GENERATED_BODY()

public:
	AMovingPlatform();

	UPROPERTY(EditAnywhere, Category = "Platform")
	float TravelSpeed = 150.f;

	UPROPERTY(EditAnywhere, Category = "Platform")
	FVector Origin;

	UPROPERTY(EditAnywhere, Category = "Platform")
	FVector Destination;

	UPROPERTY(EditAnywhere, Category = "Platform")
	float EaseExponent = 2.f;

protected:
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
	class UBoxComponent* Collider;

private:
	float TravelDuration = 0.f;
	float ElapsedTime = 0.f;
};
