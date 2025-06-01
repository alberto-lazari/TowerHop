#include "Enemy.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TowerHop/TowerHopCharacter.h"

AEnemy::AEnemy()
{
    if (UCapsuleComponent* Collider = GetCapsuleComponent())
    {
        // Bind hit event
        Collider->OnComponentHit.AddDynamic(this, &AEnemy::OnHit);
    }
}

void AEnemy::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    if (!OtherActor || OtherActor == this)
    {
        return;
    }

    // Cast to your player class (replace AMyPlayerCharacter with your player class)
    if (ATowerHopCharacter* Player = Cast<ATowerHopCharacter>(OtherActor))
    {
        // Player takes damage
        UGameplayStatics::ApplyDamage(Player, 1.f, GetController(), this, nullptr);
    }
}
