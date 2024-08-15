// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUD.generated.h"


/**
 * 
 */
UCLASS()
class MYSHOOTER_API APlayerHUD : public AHUD
{
    GENERATED_BODY()

public:
    // Override de la función BeginPlay para inicializar el HUD
    virtual void BeginPlay() override;

protected:
    // Clase del Widget Blueprint que se usará para el HUD
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
    TSubclassOf<UUserWidget> HUDWidgetClass;

    // Instancia del Widget
    UPROPERTY()
    UUserWidget* HUDWidget;

private:
    // Funciones para mostrar las pantallas de ganar o perder
    void ShowWinScreen();
    void ShowLoseScreen();
};
