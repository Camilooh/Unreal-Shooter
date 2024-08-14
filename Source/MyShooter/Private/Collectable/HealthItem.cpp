// Fill out your copyright notice in the Description page of Project Settings.


#include "Collectable/HealthItem.h"
#include "MyCharacter.h" // Incluye la cabecera del jugador si es necesario

AHealthItem::AHealthItem()
{
    // Configura cualquier propiedad espec�fica del HealthItem aqu�
}

void AHealthItem::OnPlayerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    Super::OnPlayerOverlap(OverlappedComponent, OtherActor, OtherComponent, OtherBodyIndex, bFromSweep, SweepResult);

    if (OtherActor && (OtherActor != this) && OtherActor->IsA(AMyCharacter::StaticClass()))
    {
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, TEXT("Health Recolected"));
        }
        // L�gica espec�fica para recolectar salud
        Destroy();
    }
}
