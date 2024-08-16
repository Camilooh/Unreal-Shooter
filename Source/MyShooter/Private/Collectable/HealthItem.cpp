// Fill out your copyright notice in the Description page of Project Settings.


#include "Collectable/HealthItem.h"
#include "MyCharacter.h" // Incluye la cabecera del jugador si es necesario
#include "Kismet/GameplayStatics.h"

AHealthItem::AHealthItem()
{
    // Configura cualquier propiedad específica del HealthItem aquí
}

void AHealthItem::OnPlayerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    Super::OnPlayerOverlap(OverlappedComponent, OtherActor, OtherComponent, OtherBodyIndex, bFromSweep, SweepResult);
    AMyCharacter* MyCharacter = Cast<AMyCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
    if (OtherActor && (OtherActor != this) && OtherActor->IsA(AMyCharacter::StaticClass()))
    {
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, TEXT("Health Recolected"));
        }
        // Lógica específica para recolectar salud

        MyCharacter->AddHealth(5);
        Destroy();
    }
}
