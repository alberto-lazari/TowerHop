#include "TowerHopHUD.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "Components/HorizontalBox.h"
#include "Components/VerticalBox.h"
#include "GameHUDWidget.h"
#include "PlayerHealthWidget.h"
#include "PlayerCollectiblesWidget.h"

DEFINE_LOG_CATEGORY_STATIC(LogTowerHopHUD, Log, All);

ATowerHopHUD::ATowerHopHUD()
{
	// Assign the Game HUD Widget Blueprint
	static ConstructorHelpers::FClassFinder<UGameHUDWidget> GameHUDObj(TEXT("/Game/UI/WBP_GameHUD"));
	if (GameHUDObj.Succeeded())
	{
		GameHUDClass = GameHUDObj.Class;
	}
	else
	{
		UE_LOG(LogTowerHopHUD, Error, TEXT("Failed to find WBP_GameHUD"));
	}

	// Assign the Player Health Widget Blueprint
	static ConstructorHelpers::FClassFinder<UPlayerHealthWidget> HealthWidgetObj(TEXT("/Game/UI/WBP_PlayerHealth"));
	if (HealthWidgetObj.Succeeded())
	{
		PlayerHealthWidgetClass = HealthWidgetObj.Class;
	}
	else
	{
		UE_LOG(LogTowerHopHUD, Error, TEXT("Failed to find WBP_PlayerHealth"));
	}

	// Assign the Player Health Widget Blueprint
	static ConstructorHelpers::FClassFinder<UPlayerCollectiblesWidget> CollectiblesWidgetObj(TEXT("/Game/UI/WBP_PlayerCollectibles"));
	if (CollectiblesWidgetObj.Succeeded())
	{
		PlayerCollectiblesWidgetClass = CollectiblesWidgetObj.Class;
	}
	else
	{
		UE_LOG(LogTowerHopHUD, Error, TEXT("Failed to find WBP_PlayerCollectibles"));
	}
}

void ATowerHopHUD::BeginPlay()
{
	Super::BeginPlay();

	CreateHUDWidget(GetWorld());
}

void ATowerHopHUD::CreateHUDWidget(UWorld* World)
{
	if (!GameHUDClass)
	{
		UE_LOG(LogTowerHopHUD, Error, TEXT("GameHUD class not assigned"));
		return;
	}

	GameHUDWidget = CreateWidget<UGameHUDWidget>(World, GameHUDClass);
	if (!GameHUDWidget) return;

	GameHUDWidget->AddToViewport();

	// Create PlayerHealthWidget and add it to its container
	if (PlayerHealthWidgetClass)
	{
		PlayerHealthWidget = CreateWidget<UPlayerHealthWidget>(World, PlayerHealthWidgetClass);
		if (PlayerHealthWidget)
		{
			GameHUDWidget->HealthContainer->AddChild(PlayerHealthWidget);
		}
	}

	// Create PlayerCollectiblesWidget and add it to its container
	if (PlayerCollectiblesWidgetClass)
	{
		PlayerCollectiblesWidget = CreateWidget<UPlayerCollectiblesWidget>(World, PlayerCollectiblesWidgetClass);
		if (PlayerCollectiblesWidget)
		{
			GameHUDWidget->CollectiblesContainer->AddChild(PlayerCollectiblesWidget);
		}
	}
}

void ATowerHopHUD::UpdateHealthUI(int32 Health, int32 MaxHealth)
{
	if (PlayerHealthWidget)
	{
		PlayerHealthWidget->UpdateHearts(Health, MaxHealth);
	}
}

void ATowerHopHUD::UpdateCoinsUI(int32 CoinCount)
{
	if (PlayerCollectiblesWidget)
	{
		PlayerCollectiblesWidget->SetCoinCount(CoinCount);
	}
}
