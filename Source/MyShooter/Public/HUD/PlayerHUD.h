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
    //override de Tick
    virtual void Tick(float DeltaTime) override;

    // Función para actualizar el número de enemigos en el HUD
    void UpdateEnemyCount();

    // Función para actualizar el texto de la munición en el HUD
    void UpdateAmmoCount();

    // Función para actualizar la barra de salud en el HUD
    void UpdateHealthBar();
    // Funciones para mostrar las pantallas de ganar o perder
    void ShowWinScreen();
    void ShowLoseScreen();

   
protected:

    // Clase del Widget Blueprint que se usará para el HUD
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
    TSubclassOf<UUserWidget> HUDWidgetClass;

    // Instancia del Widget
    UPROPERTY()
    UUserWidget* HUDWidget;

    // Función que se llamará cuando se haga clic en el botón del menú principal
    UFUNCTION()
    void OnMainMenuButtonClicked();
   
};
