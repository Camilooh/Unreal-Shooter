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

private:
    UPROPERTY(EditAnywhere)
    UStaticMeshComponent* MeshComponent;

    UPROPERTY(EditAnywhere)
    class USphereComponent* DetectionSphere;

    UPROPERTY(EditAnywhere)
    TSubclassOf<class AProjectile> ProjectileClass;

    UFUNCTION()
    void OnDetectionSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    void FireAtPlayer();
};
