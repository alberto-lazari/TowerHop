#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TowerHopHUD.generated.h"

UCLASS()
class TOWERHOP_API ATowerHopHUD : public AHUD
{
	GENERATED_BODY()

public:
	ATowerHopHUD();

	UFUNCTION()
	void UpdateHealthUI(int32 Health, int32 MaxHealth);

	UFUNCTION()
	void UpdateCoinsUI(int32 CoinCount);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> GameHUDClass;

	UPROPERTY()
	class UGameHUDWidget* GameHUDWidget;


	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> PlayerHealthWidgetClass;

	UPROPERTY()
	class UPlayerHealthWidget* PlayerHealthWidget;


	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> PlayerCollectiblesWidgetClass;

	UPROPERTY()
	class UPlayerCollectiblesWidget* PlayerCollectiblesWidget;

private:
	void CreateHUDWidget(UWorld* World);
};
