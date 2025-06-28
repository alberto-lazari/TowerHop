#include "TowerHopGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameUserSettings.h"

void UTowerHopGameInstance::StartNewGame()
{
	UGameplayStatics::OpenLevel(this, FName("World1Map"));
}

void UTowerHopGameInstance::ReturnToMainMenu()
{
	UGameplayStatics::OpenLevel(this, FName("MainMenuMap"));
}

void UTowerHopGameInstance::CycleGraphicsQuality()
{
    UGameUserSettings* Settings = GEngine->GetGameUserSettings();
    int32 Quality = Settings->GetOverallScalabilityLevel();
    Settings->SetOverallScalabilityLevel((Quality + 1) % 4);
    Settings->ApplySettings(false);
    Settings->SaveSettings();
}

void UTowerHopGameInstance::QuitGame()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, true);
}

FString UTowerHopGameInstance::GraphicsQualityText() const
{
    int32 Quality = UGameUserSettings::GetGameUserSettings()->GetOverallScalabilityLevel();

    switch (Quality)
    {
        case 0: return TEXT("Potato");
        case 1: return TEXT("Ok");
        case 2: return TEXT("Cool");
        case 3: return TEXT("OMG");
        default: return TEXT("Huh?");
    }
}
