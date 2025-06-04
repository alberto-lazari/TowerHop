#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TowerHopHUD.generated.h"

class UGameHUDWidget;
class UPlayerHealthWidget;

UCLASS()
class TOWERHOP_API ATowerHopHUD : public AHUD
{
    GENERATED_BODY()

public:
	ATowerHopHUD();

    UFUNCTION()
    void UpdateHealthUI(int32 Health, int32 MaxHealth);

protected:
    virtual void BeginPlay() override;

    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<UUserWidget> GameHUDClass;

    UPROPERTY()
    UGameHUDWidget* GameHUDWidget;


    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<UUserWidget> PlayerHealthWidgetClass;

    UPROPERTY()
    UPlayerHealthWidget* PlayerHealthWidget;
};
