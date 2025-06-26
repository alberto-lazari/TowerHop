#include "TowerHopGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "TowerHop/Characters/PlayerCharacter.h"
#include "TowerHop/Controllers/PlayerCharacterController.h"
#include "TowerHop/UI/TowerHopHUD.h"

ATowerHopGameMode::ATowerHopGameMode()
{
	// Set default pawn class to player's blueprint
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Character/BP_PlayerCharacter"));
	if (PlayerPawnBPClass.Class)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// Set custom player controller
	PlayerControllerClass = APlayerCharacterController::StaticClass();

	// Set HUD
	HUDClass = ATowerHopHUD::StaticClass();

	// Load the soundtrack audio asset
	static ConstructorHelpers::FObjectFinder<USoundBase> SoundtrackAsset(TEXT("/Game/World/SW_Soundtrack.SW_Soundtrack"));
	if (SoundtrackAsset.Succeeded())
	{
		Soundtrack = SoundtrackAsset.Object;
	}
}

void ATowerHopGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (Soundtrack)
	{
		Music = UGameplayStatics::SpawnSound2D(this, Soundtrack, 1.f, 1.f, 0.f, nullptr, true);
	}
}

void ATowerHopGameMode::HandlePlayerDeath()
{
	// Delay game restart
	float Delay = 1.5f;
	GetWorldTimerManager().SetTimer(GameOverTimer, this, &ATowerHopGameMode::GameOver, Delay, false);
}

void ATowerHopGameMode::HandleBossDeath()
{
	FTimerManager& TimerManager = GetWorldTimerManager();

	if (APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0)))
	{
		TimerManager.SetTimer(PlayerWinAnimationTimer, Player, &APlayerCharacter::PlayWinAnimation, WinAnimationDelay, false);
	}

	TimerManager.SetTimer(FadeToBlackTimer, this, &ATowerHopGameMode::FadeToBlack, FadeDelay, false);
}

void ATowerHopGameMode::FadeToBlack()
{
	// Delay game end
	GetWorldTimerManager().SetTimer(GameOverTimer, this, &ATowerHopGameMode::GameOver, FadeDuration, false);

	if (APlayerController* Controller = Cast<APlayerController>(UGameplayStatics::GetPlayerController(this, 0)))
	{
		if (Controller->PlayerCameraManager)
		{
			Controller->PlayerCameraManager->StartCameraFade(
				// (from, to) alpha
				0.0f, 1.0f,
				FadeDuration,
				FLinearColor::Black,
				// Fade audio
				true,
				// Hold the fade afterwards
				true
			);
		}
	}
}

void ATowerHopGameMode::GameOver()
{
	// On game over return to main menu
	UGameplayStatics::OpenLevel(this, FName("MainMenuMap"), false);
}
