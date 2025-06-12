#include "PlayerCollectiblesWidget.h"
#include "Components/TextBlock.h"

void UPlayerCollectiblesWidget::SetCoinCount(int32 CoinCount)
{
	if (!CoinCountText) return;

	CoinCountText->SetText(FText::FromString(FString::Printf(TEXT("x %d"), CoinCount)));
}
