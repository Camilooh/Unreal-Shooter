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
    // Override de la funci�n BeginPlay para inicializar el HUD
    virtual void BeginPlay() override;
    //override de Tick
    virtual void Tick(float DeltaTime) override;

    // Funci�n para actualizar el n�mero de enemigos en el HUD
    void UpdateEnemyCount();

    // Funci�n para actualizar el texto de la munici�n en el HUD
    void UpdateAmmoCount();

    // Funci�n para actualizar la barra de salud en el HUD
    void UpdateHealthBar();
    // Funciones para mostrar las pantallas de ganar o perder
    void ShowWinScreen();
    void ShowLoseScreen();

   
protected:

    // Clase del Widget Blueprint que se usar� para el HUD
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
    TSubclassOf<UUserWidget> HUDWidgetClass;

    // Instancia del Widget
    UPROPERTY()
    UUserWidget* HUDWidget;

    // Funci�n que se llamar� cuando se haga clic en el bot�n del men� principal
    UFUNCTION()
    void OnMainMenuButtonClicked();
   
};
