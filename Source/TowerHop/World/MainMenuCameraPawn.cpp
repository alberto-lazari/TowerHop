#include "MainMenuCameraPawn.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"

AMainMenuCameraPawn::AMainMenuCameraPawn()
{
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
}
