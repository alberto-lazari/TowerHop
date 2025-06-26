#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainMenuController.generated.h"

UCLASS()
class TOWERHOP_API AMainMenuController : public APlayerController
{
	GENERATED_BODY()

public:
	AMainMenuController();

	UPROPERTY(EditAnywhere)
	FName GameMap = "World1Map";

	UFUNCTION(BlueprintCallable)
	void StartNewGame();

	UFUNCTION(BlueprintCallable)
	void QuitGame();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> MainMenuWidgetClass;

	UPROPERTY()
	class UMainMenuWidget* MainMenuWidget;
};
