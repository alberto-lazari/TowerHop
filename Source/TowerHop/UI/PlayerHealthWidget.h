#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/HorizontalBox.h"
#include "Components/Image.h"
#include "PlayerHealthWidget.generated.h"

UCLASS()
class TOWERHOP_API UPlayerHealthWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
    void UpdateHearts(int32 Health, int32 MaxHealth);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    UTexture2D* HeartTexture;

protected:
    virtual void NativeConstruct() override;

    UPROPERTY(meta = (BindWidget))
    UHorizontalBox* HeartsContainer;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
    float HeartSize = 50.f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
    float HeartPadding = 10.f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
    float LostHeartOpacity = 0.3f;
};
