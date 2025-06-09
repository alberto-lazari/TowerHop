#include "PlayerHealthWidget.h"
#include "Components/SizeBox.h"
#include "Components/HorizontalBoxSlot.h"

void UPlayerHealthWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UPlayerHealthWidget::UpdateHearts(int32 Health, int32 MaxHealth)
{
	if (!HeartsContainer || !HeartTexture) return;

	HeartsContainer->ClearChildren();

	for (int32 i = 0; i < MaxHealth; ++i)
	{
		UImage* Heart = NewObject<UImage>(this);
		FSlateBrush Brush;
		Brush.SetResourceObject(HeartTexture);
		// Brush.ImageSize = FVector2D(32.f, 32.f);
		Heart->SetBrush(Brush);

		// Display transparent lost hearts
		Heart->SetOpacity(i < Health ? 1.f : LostHeartOpacity);

		// Wrap in size box
		USizeBox* SizeBox = NewObject<USizeBox>(this);
		SizeBox->SetWidthOverride(HeartSize);
		SizeBox->SetHeightOverride(HeartSize);
		SizeBox->AddChild(Heart);

		// Add to horizontal box
		if (UHorizontalBoxSlot* Slot = HeartsContainer->AddChildToHorizontalBox(SizeBox))
		{
			Slot->SetPadding(FMargin(HeartPadding));
			Slot->SetHorizontalAlignment(HAlign_Left);
			Slot->SetVerticalAlignment(VAlign_Center);
		}
	}
}
