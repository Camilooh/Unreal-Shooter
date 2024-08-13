// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/PlayerHUD.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void APlayerHUD::BeginPlay()
{
    Super::BeginPlay();

    // Comprueba si la clase del widget está asignada
    if (HUDWidgetClass != nullptr)
    {
        // Crea el widget y agrégalo al viewport
        HUDWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);
        if (HUDWidget)
        {
            HUDWidget->AddToViewport();
        }
    }
}

void APlayerHUD::UpdateHealth(float HealthPercent)
{
    if (HUDWidget)
    {
        UProgressBar* HealthBar = Cast<UProgressBar>(HUDWidget->GetWidgetFromName(TEXT("HealthBar")));
        if (HealthBar)
        {
            HealthBar->SetPercent(HealthPercent);
        }
    }
}

void APlayerHUD::UpdateAmmo(int32 AmmoCount)
{
    if (HUDWidget)
    {
        UTextBlock* AmmoText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("AmmoText")));
        if (AmmoText)
        {
            AmmoText->SetText(FText::FromString(FString::Printf(TEXT("Ammo: %d"), AmmoCount)));
        }
    }
}
