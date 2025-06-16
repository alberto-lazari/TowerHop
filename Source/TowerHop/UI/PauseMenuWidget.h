#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseMenuWidget.generated.h"

class UButton;

UCLASS()
class TOWERHOP_API UPauseMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void OnResumeClicked();

	UFUNCTION(BlueprintCallable)
	void OnNewGameClicked();

	UFUNCTION(BlueprintCallable)
	void OnQuitClicked();

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	UButton* ResumeButton;

	UPROPERTY(meta = (BindWidget))
	UButton* NewGameButton;

	UPROPERTY(meta = (BindWidget))
	UButton* QuitButton;

private:
	class APlayerCharacterController* PlayerController;
};
