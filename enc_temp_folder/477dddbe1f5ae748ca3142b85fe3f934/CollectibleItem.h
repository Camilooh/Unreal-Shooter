// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CollectibleItem.generated.h"

UCLASS()
class MYSHOOTER_API ACollectibleItem : public AActor
{
    GENERATED_BODY()

public:
    ACollectibleItem();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    UFUNCTION()
    void OnPlayerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* MeshComponent;
};