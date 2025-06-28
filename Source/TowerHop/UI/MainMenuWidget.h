#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

class UButton;

UCLASS()
class TOWERHOP_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	UButton* NewGameButton;

	UPROPERTY(meta = (BindWidget))
	UButton* GraphicsButton;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* GraphicsButtonText;

	UPROPERTY(meta = (BindWidget))
	UButton* QuitButton;

	UFUNCTION()
	void OnGraphicsButtonClick();

private:
	class UTowerHopGameInstance* GameInstance;

	void UpdateGraphicsButtonText();
};
