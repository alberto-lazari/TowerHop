#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerCollectiblesWidget.generated.h"

UCLASS()
class TOWERHOP_API UPlayerCollectiblesWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetCoinCount(int32 CoinCount);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	UTexture2D* CoinTexture;

protected:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* CoinCountText;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	float CoinSize = 50.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	float CoinPadding = 10.f;
};
