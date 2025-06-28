#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Lever.generated.h"

UCLASS()
class TOWERHOP_API ALever : public AActor
{
	GENERATED_BODY()

public:
	ALever();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lever")
	bool bActive = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lever")
	class AMovingPlatform* ControlledPlatform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
	float HitBounceSpeed = 600.f;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USkeletalMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
	class UBoxComponent* Collider;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
	class USphereComponent* HandleCollider;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation")
	UAnimSequence* ActivateAnimation;

	UFUNCTION()
	void OnLeverActivated(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);
};
