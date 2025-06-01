#pragma once

#include "TowerHopCharacterAnimInstance.generated.h"

UCLASS(transient, Blueprintable, hideCategories=AnimInstance, BlueprintType)
class UTowerHopCharacterAnimInstance : public UAnimInstance
{
    GENERATED_UCLASS_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Default)
    bool bDead = false;
};
