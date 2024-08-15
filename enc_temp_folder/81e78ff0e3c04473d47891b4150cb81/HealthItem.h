// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Collectable/CollectibleItem.h"
#include "HealthItem.generated.h"

/**
 * 
 */
UCLASS()
class MYSHOOTER_API AHealthItem : public ACollectibleItem
{
    GENERATED_BODY()

public:
    AHealthItem();

protected:
    virtual void OnPlayerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
};
