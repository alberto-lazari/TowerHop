#include "Boss.h"
#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "TowerHop/GameModes/TowerHopGameMode.h"

ABoss::ABoss()
{
	// Default to 3 lives
	Health = MaxHealth = 3;
}

FVector ABoss::BounceDirection(const APlayerCharacter* Player) const
{
	FVector TowardsPatrolCenter = (PatrolCenter - Player->GetActorLocation()).GetSafeNormal2D();
	return (TowardsPatrolCenter + FVector::UpVector).GetSafeNormal();
}

void ABoss::Die()
{
	AEnemy::Die();

	if (ATowerHopGameMode* GameMode = Cast<ATowerHopGameMode>(UGameplayStatics::GetGameMode(this)))
	{
		GameMode->HandleBossDeath();
	}
}
