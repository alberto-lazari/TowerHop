#include "TowerHopHUD.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "GameHUDWidget.h"
#include "PlayerHealthWidget.h"

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
		UE_LOG(LogTemp, Error, TEXT("Failed to find WBP_GameHUD"));
	}

	// Assign the Player Health Widget Blueprint
	static ConstructorHelpers::FClassFinder<UPlayerHealthWidget> HealthWidgetObj(TEXT("/Game/UI/WBP_PlayerHealth"));
	if (HealthWidgetObj.Succeeded())
	{
		PlayerHealthWidgetClass = HealthWidgetObj.Class;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to find WBP_PlayerHealth"));
	}
}

void ATowerHopHUD::BeginPlay()
{
	Super::BeginPlay();

	if (GameHUDClass)
	{
		GameHUDWidget = CreateWidget<UGameHUDWidget>(GetWorld(), GameHUDClass);
		if (GameHUDWidget)
		{
			GameHUDWidget->AddToViewport();

			// Create PlayerHealthWidget and add it to the HealthContainer
			if (PlayerHealthWidgetClass)
			{
				PlayerHealthWidget = CreateWidget<UPlayerHealthWidget>(GetWorld(), PlayerHealthWidgetClass);
				if (PlayerHealthWidget)
				{
					GameHUDWidget->HealthContainer->AddChildToHorizontalBox(PlayerHealthWidget);
				}
			}
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
