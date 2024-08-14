// Fill out your copyright notice in the Description page of Project Settings.


#include "Collectable/CollectibleItem.h"
#include "Components/StaticMeshComponent.h"
#include "MyCharacter.h" // Incluye la cabecera del jugador si es necesario

ACollectibleItem::ACollectibleItem()
{
    PrimaryActorTick.bCanEverTick = true;

    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    RootComponent = MeshComponent;

    // Configura el evento de superposición
    MeshComponent->OnComponentBeginOverlap.AddDynamic(this, &ACollectibleItem::OnPlayerOverlap);
}

void ACollectibleItem::BeginPlay()
{
    Super::BeginPlay();
}

void ACollectibleItem::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ACollectibleItem::OnPlayerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && (OtherActor != this) && OtherActor->IsA(AMyCharacter::StaticClass()))
    {
        UE_LOG(LogTemp, Warning, TEXT("Item destroyed: %s"), *GetName());
        Destroy();
    }
}

