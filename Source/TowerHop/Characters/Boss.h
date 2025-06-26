#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "Boss.generated.h"

UCLASS()
class TOWERHOP_API ABoss : public AEnemy
{
	GENERATED_BODY()

public:
	ABoss();

protected:
	virtual FVector BounceDirection(class APlayerCharacter const* Player) const override;

	virtual void Die() override;
};
