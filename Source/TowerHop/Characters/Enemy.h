#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

class USphereComponent;

UCLASS()
class TOWERHOP_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	AEnemy();

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	int32 MaxHealth = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	int32 Health = MaxHealth;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
	USphereComponent* HeadCollider;

	UFUNCTION()
	void OnBodyHit(
		UPrimitiveComponent* HitComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		FVector NormalImpulse,
		const FHitResult& Hit
	);

	UFUNCTION()
	void OnHeadOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

	virtual float TakeDamage(
		float DamageAmount,
		const FDamageEvent& DamageEvent,
		AController* EventInstigator,
		AActor* DamageCauser
	) override;

	void Die();

	UPROPERTY(EditDefaultsOnly, Category = "Collision")
	float HitBounceSpeed = 600.f;

	// Crushing animation fields
	UPROPERTY(EditDefaultsOnly, Category = "Crush")
	float CrushDuration = 0.15f;

	UPROPERTY(EditDefaultsOnly, Category = "Crush")
	float DestroyDelay = 0.3f;

	UPROPERTY(EditDefaultsOnly, Category = "Crush")
	FVector CrushedScale = FVector(1.f, 1.f, 0.1f);

	UPROPERTY(EditDefaultsOnly, Category = "Crush")
	FVector SquishedScale = FVector(1.f, 1.f, 0.5f);

private:
	bool bIsAnimating = false;
	bool bRestoreAfterAnimation = false;
	float AnimationTimer = 0.f;
	float AnimationDuration;
	FVector InitialLocation;
	FVector InitialScale;
	FVector TargetScale;
	float CapsuleHalfHeight;

	void StartScaleAnimation(FVector TargetScale, float Duration, bool bRestore = false);
	void PlayScaleAnimation(float DeltaTime);
};
