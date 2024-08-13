// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/PlayGameMode.h"
#include "HUD/PlayerHUD.h"

void APlayGameMode::BeginPlay() 
{
    Super::BeginPlay();

    if (HUDWidgetClass)
    {
        UUserWidget* MenuWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);
        if (MenuWidget)
        {
            MenuWidget->AddToViewport();
        }
    }
}

