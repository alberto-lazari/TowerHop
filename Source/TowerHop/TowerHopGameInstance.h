#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "TowerHopGameInstance.generated.h"

UCLASS()
class TOWERHOP_API UTowerHopGameInstance : public UGameInstance
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
    void StartNewGame();

    UFUNCTION(BlueprintCallable)
    void CycleGraphicsQuality();

	UFUNCTION(BlueprintCallable)
	void ReturnToMainMenu();

    UFUNCTION(BlueprintCallable)
    void QuitGame();

	FString GraphicsQualityText() const;
};
