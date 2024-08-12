#include "MainMenuGameMode.h"
#include "MainMenuWidget.h"
#include "Blueprint/UserWidget.h"

void AMainMenuGameMode::BeginPlay()
{
    Super::BeginPlay();

    if (MenuWidgetClass)
    {
        UUserWidget* MenuWidget = CreateWidget<UUserWidget>(GetWorld(), MenuWidgetClass);
        if (MenuWidget)
        {
            MenuWidget->AddToViewport();
        }
    }
}
