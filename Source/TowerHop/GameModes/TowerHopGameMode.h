#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TowerHopGameMode.generated.h"

UCLASS(minimalapi)
class ATowerHopGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATowerHopGameMode();

	UFUNCTION(BlueprintCallable)
	void HandlePlayerDeath();

	UFUNCTION(BlueprintCallable)
	void HandleBossDeath();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Timer")
	float WinAnimationDelay = 2.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Timer")
	float FadeDelay = 3.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Timer")
	float FadeDuration = 1.f;

private:
	FTimerHandle GameOverTimer;
	FTimerHandle PlayerWinAnimationTimer;
	FTimerHandle FadeToBlackTimer;

	void FadeToBlack();
	void GameOver();
};
