#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "PauseMenuWidget.generated.h"

class UButton;

UCLASS()
class TOWERHOP_API UPauseMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetFocus() const;

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	UButton* ResumeButton;

	UPROPERTY(meta = (BindWidget))
	UButton* NewGameButton;

	UPROPERTY(meta = (BindWidget))
	UButton* GraphicsButton;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* GraphicsButtonText;

	UPROPERTY(meta = (BindWidget))
	UButton* MainMenuButton;

	UPROPERTY(meta = (BindWidget))
	UButton* QuitButton;

	UFUNCTION()
	void OnGraphicsButtonClick();

private:
	class UTowerHopGameInstance* GameInstance;
	class APlayerCharacterController* PlayerController;

	void UpdateGraphicsButtonText();
};
