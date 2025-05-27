#include "AEnemy.h"
#include "Components/CapsuleComponent.h"

AEnemy::AEnemy()
{
    UCapsuleComponent* collider = GetCapsuleComponent();
    if (collider)
    {
        // Bind hit event
        collider->OnComponentHit.AddDynamic(this, &AEnemy::OnHit);
    }
}

void AEnemy::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Hit"));
}
