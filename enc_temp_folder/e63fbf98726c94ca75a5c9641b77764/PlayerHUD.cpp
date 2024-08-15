// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/PlayerHUD.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"


void APlayerHUD::BeginPlay()
{
    Super::BeginPlay();
   
    // Verifica si se ha asignado una clase de Widget Blueprint
    if (HUDWidgetClass)
    {
        // Crea una instancia del Widget Blueprint
        HUDWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);

        // Verifica si la creación del widget fue exitosa
        if (HUDWidget)
        {
            // Añade el widget al viewport
            HUDWidget->AddToViewport();
            
        }
    }

    // Configura los bindings para las teclas
    if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0))
    {
        PlayerController->InputComponent->BindAction("ShowWinScreen", IE_Pressed, this, &APlayerHUD::ShowWinScreen);
        PlayerController->InputComponent->BindAction("ShowLoseScreen", IE_Pressed, this, &APlayerHUD::ShowLoseScreen);
    }

}

void APlayerHUD::ShowWinScreen()
{
    if (HUDWidget)
    {
       
        // Mostrar el elemento de Win Screen
        UWidget* WinScreenWidget = HUDWidget->GetWidgetFromName(TEXT("WinScreenElement"));
        if (WinScreenWidget)
        {
           
            WinScreenWidget->SetVisibility(ESlateVisibility::Visible);
        }
    }
    else
    {
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Se agrego el widget"));
        }
    }
}

void APlayerHUD::ShowLoseScreen()
{
    if (HUDWidget)
    {
        // Mostrar el elemento de Lose Screen
        UWidget* LoseScreenWidget = HUDWidget->GetWidgetFromName(TEXT("LoseScreenElement"));
        if (LoseScreenWidget)
        {
            LoseScreenWidget->SetVisibility(ESlateVisibility::Visible);
        }
    }
}


