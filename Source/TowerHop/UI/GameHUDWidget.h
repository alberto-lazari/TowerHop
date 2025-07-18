#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameHUDWidget.generated.h"

UCLASS()
class TOWERHOP_API UGameHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	class UHorizontalBox* HealthContainer;

	UPROPERTY(meta = (BindWidget))
	class UVerticalBox* CollectiblesContainer;
};
