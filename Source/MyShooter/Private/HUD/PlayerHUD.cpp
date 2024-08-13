// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/PlayerHUD.h"
#include "Blueprint/UserWidget.h"

void APlayerHUD::BeginPlay()
{
    Super::BeginPlay();

    // Verifica si se ha asignado una clase de Widget Blueprint
    if (HUDWidgetClass)
    {
        // Crea una instancia del Widget Blueprint
        HUDWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);

        // Verifica si la creaci�n del widget fue exitosa
        if (HUDWidget)
        {
            // A�ade el widget al viewport
            HUDWidget->AddToViewport();
        }
    }
}


