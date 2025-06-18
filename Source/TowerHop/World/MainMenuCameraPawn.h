#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MainMenuCameraPawn.generated.h"

UCLASS()
class TOWERHOP_API AMainMenuCameraPawn : public APawn
{
	GENERATED_BODY()

public:
	AMainMenuCameraPawn();

private:
	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* CameraComponent;
};
