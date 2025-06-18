#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "TowerHop/UI/PlayerHealthWidget.h"
#include "PlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class ATowerHopHUD;

DECLARE_LOG_CATEGORY_EXTERN(LogPlayerCharacter, Log, All);

UCLASS(config=Game)
class APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* TogglePauseAction;

	ATowerHopHUD* HUD;

public:
	APlayerCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	int32 MaxHealthLimit = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	int32 MaxHealth = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	int32 Health = MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collectible")
	int32 Coins = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collectible")
	int32 CoinsPerHeart = 10;

	void PickCoin(int32 CoinValue);

protected:
	virtual void BeginPlay() override;

	virtual float TakeDamage(
		float DamageAmount,
		const FDamageEvent& DamageEvent,
		AController* EventInstigator,
		AActor* DamageCauser
	) override;

	virtual void NotifyControllerChanged() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	void Die();

	void TogglePauseMenu();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	UAnimMontage* HitReactMontage;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};
