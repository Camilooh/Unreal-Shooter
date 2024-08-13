// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PlayerHUD.generated.h"

/**
 * 
 */
UCLASS()
class MYSHOOTER_API APlayerHUD : public AHUD
{
    GENERATED_BODY()

public:
    virtual void BeginPlay() override;

protected:
    // Clase del widget HUD que se asignará en el editor
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    TSubclassOf<class UUserWidget> HUDWidgetClass;

    // Referencia al widget HUD creado
    UPROPERTY()
    class UUserWidget* HUDWidget;

public:
    // Método para actualizar la barra de salud
    void UpdateHealth(float HealthPercent);

    // Método para actualizar el texto de balas restantes
    void UpdateAmmo(int32 AmmoCount);
};
