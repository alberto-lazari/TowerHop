#pragma once

#include "PlayerAnimInstance.generated.h"

UCLASS(transient, Blueprintable, hideCategories=AnimInstance, BlueprintType)
class UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_UCLASS_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Default)
	bool bDead = false;
};
