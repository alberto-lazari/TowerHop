// Copyright Epic Games, Inc. All Rights Reserved.

#include "PlayerCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerAnimInstance.h"
#include "TowerHop/GameModes/TowerHopGameMode.h"
#include "TowerHop/UI/TowerHopHUD.h"
#include "TowerHop/Controllers/PlayerCharacterController.h"

DEFINE_LOG_CATEGORY(LogPlayerCharacter);

//////////////////////////////////////////////////////////////////////////
// APlayerCharacter

APlayerCharacter::APlayerCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character)
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	HUD = Cast<ATowerHopHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	if (HUD)
	{
		HUD->UpdateHealthUI(Health, MaxHealth);
		HUD->UpdateCoinsUI(0);
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void APlayerCharacter::NotifyControllerChanged()
{
	Super::NotifyControllerChanged();

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		Input->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		Input->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);

		// Looking
		Input->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);

		// Toggle pause menu
		Input->BindAction(TogglePauseAction, ETriggerEvent::Triggered, this, &APlayerCharacter::TogglePauseMenu);
	}
	else
	{
		UE_LOG(LogPlayerCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component!"), *GetNameSafe(this));
	}
}

void APlayerCharacter::PickCoin(int32 CoinValue)
{
	if (CoinValue <= 0) return;

	Coins += CoinValue;

	if (Coins % CoinsPerHeart == 0)
	{
		// Player picked enough coin to get a heart.
		// Increment current health and check if a new heart is gained
		if (++Health > MaxHealth
			// If so, increment the number of hearts and check if it overflowed the limit
			&& ++MaxHealth > MaxHealthLimit)
		{
			// Reset current health to the maximum limit if it overflowed
			Health = MaxHealth = MaxHealthLimit;
		}

		if (HUD)
		{
			HUD->UpdateHealthUI(Health, MaxHealth);
		}
	}

	if (HUD)
	{
		HUD->UpdateCoinsUI(Coins);
	}
}

float APlayerCharacter::TakeDamage(float DamageAmount, const FDamageEvent& DamageEvent,
		AController* EventInstigator, AActor* DamageCauser)
{
	// If already dead do nothing
	if (Health <= 0) return 0.f;

	Health = FMath::Max(0, Health - static_cast<int32>(DamageAmount));

	// Update UI
	if (HUD)
	{
		HUD->UpdateHealthUI(Health, MaxHealth);
	}

	if (Health <= 0)
	{
		Die();
	}
	else if (HitReactMontage)
	{
		// Trigger hit animation
		if (USkeletalMeshComponent* Mesh = GetMesh())
		{
			if (UPlayerAnimInstance* AnimInstance = Cast<UPlayerAnimInstance>(Mesh->GetAnimInstance()))
			{
				AnimInstance->Montage_Play(HitReactMontage);
			}
		}
	}

	return DamageAmount;
}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void APlayerCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void APlayerCharacter::Die()
{
	// Stop character and disable any further input
	GetCharacterMovement()->DisableMovement();
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		PlayerController->DisableInput(PlayerController);
	}

	// Trigger death animation
	if (USkeletalMeshComponent* Mesh = GetMesh())
	{
		if (UPlayerAnimInstance* AnimInstance =
				Cast<UPlayerAnimInstance>(Mesh->GetAnimInstance()))
		{
			AnimInstance->bDead = true;
		}
	}

	if (ATowerHopGameMode* GameMode = Cast<ATowerHopGameMode>(UGameplayStatics::GetGameMode(this)))
	{
		GameMode->HandlePlayerDeath();
	}
}

void APlayerCharacter::TogglePauseMenu()
{
	if (APlayerCharacterController* PlayerController = Cast<APlayerCharacterController>(Controller))
	{
		PlayerController->TogglePauseMenu();
	}
}
