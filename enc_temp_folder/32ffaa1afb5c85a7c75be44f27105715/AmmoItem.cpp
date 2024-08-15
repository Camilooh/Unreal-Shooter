// Fill out your copyright notice in the Description page of Project Settings.


#include "Collectable/AmmoItem.h"
#include "MyCharacter.h"

AAmmoItem::AAmmoItem()
{
    // Configura cualquier propiedad espec�fica del BulletItem aqu�
}
void AAmmoItem::OnPlayerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    Super::OnPlayerOverlap(OverlappedComponent, OtherActor, OtherComponent, OtherBodyIndex, bFromSweep, SweepResult);

    if (OtherActor && (OtherActor != this) && OtherActor->IsA(AMyCharacter::StaticClass()))
    {
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, TEXT("Ammo Recolected"));
        }
        // L�gica espec�fica para recolectar balas
        Destroy();
    }
}
