// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpeedReductionZone.generated.h"

UCLASS()
class MYSHOOTER_API ASpeedReductionZone : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ASpeedReductionZone();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Componente de colisión
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
    class UBoxComponent* CollisionComponent;



    // Velocidad reducida
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Speed Reduction")
    float ReducedSpeedMultiplier = 0.5f;

    // Lógica para manejar la entrada y salida del jugador
    UFUNCTION()
    void OnPlayerEnterZone(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
    void OnPlayerExitZone(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
    // Almacenar la velocidad original del jugador
    float OriginalSpeed;

    // Controlar si el jugador está dentro de la zona
    bool bIsPlayerInside;
};
