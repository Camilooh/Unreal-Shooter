#include "MainMenuWidget.h"
#include "Components/Button.h"  
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UMainMenuWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (StartButton)
    {
        StartButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnStartButtonClicked);
    }

    if (QuitButton)
    {
        QuitButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnQuitButtonClicked);
    }
}

void UMainMenuWidget::OnStartButtonClicked()
{
    UGameplayStatics::OpenLevel(this, FName("MyMap"));
}

void UMainMenuWidget::OnQuitButtonClicked()
{
    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
    //UKismetSystemLibrary::QuitGame(this, PlayerController, EQuitPreference::Quit);
}
