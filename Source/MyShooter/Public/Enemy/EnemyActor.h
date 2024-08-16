// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "EnemyActor.generated.h"

UCLASS()
class MYSHOOTER_API AEnemyActor : public AActor
{
    GENERATED_BODY()

public:
    AEnemyActor();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

public:
    /*UPROPERTY(EditAnywhere)
    UStaticMeshComponent* MeshComponent;*/

    UPROPERTY(EditAnywhere)
    class USphereComponent* DetectionSphere;

    UPROPERTY(EditAnywhere)
    TSubclassOf<class AProjectile> ProjectileClass;

    UPROPERTY(EditAnywhere, Category = "Movement")
    float MovementSpeed = 600.0f; // Velocidad de movimiento

    UPROPERTY(EditAnywhere, Category = "Movement")
    float ChangeDirectionInterval = 2.0f; // Intervalo para cambiar de dirección

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UStaticMeshComponent* MeshComponent;

private:

    FVector CurrentDirection;
    FVector TargetLocation;

    FTimerHandle TimerHandle;
    FTimerHandle FireTimerHandle;

    UFUNCTION()
    void OnDetectionSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    void FireAtPlayer();
    void MoveRandomly();
};
