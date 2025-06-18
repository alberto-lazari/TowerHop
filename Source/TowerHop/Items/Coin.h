#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Coin.generated.h"

UCLASS()
class TOWERHOP_API ACoin : public AActor
{
	GENERATED_BODY()

public:
	ACoin();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Coin")
	int32 CoinValue = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	USoundBase* PickSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	class UPointLightComponent* FlashLight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	float FlashDuration = 0.1f;

protected:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USphereComponent* Collider;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class URotatingMovementComponent* RotatingComponent;

	UFUNCTION()
	void OnPick(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

private:
	bool bFlashActive = false;
	float FlashElapsed = 0.f;
	float FlashIntensity;
};
