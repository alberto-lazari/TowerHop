// Copyright Epic Games, Inc. All Rights Reserved.

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

	void HandlePlayerDeath();

private:
	FTimerHandle RestartTimer;

	void GameOver();
};
