// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Projectile.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"


// Sets default values
AEnemyActor::AEnemyActor()
{
    PrimaryActorTick.bCanEverTick = true;

    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    RootComponent = MeshComponent;

    DetectionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("DetectionSphere"));
    DetectionSphere->SetupAttachment(RootComponent);
    DetectionSphere->InitSphereRadius(500.0f); // Ajusta el radio de detección según sea necesario
    DetectionSphere->OnComponentBeginOverlap.AddDynamic(this, &AEnemyActor::OnDetectionSphereOverlap);
}

// Called when the game starts or when spawned
void AEnemyActor::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void AEnemyActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Aquí puedes agregar la lógica para el movimiento libre del enemigo
    // Por ejemplo, podrías usar un patrón de patrullaje o un movimiento aleatorio
}

void AEnemyActor::OnDetectionSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)

{
    if (OtherActor && OtherActor != this && OtherActor->IsA(ACharacter::StaticClass())) // Verifica si es el jugador
    {
        UE_LOG(LogTemp, Warning, TEXT("Player Enter zone"));
        FireAtPlayer();
    }

}


void AEnemyActor::FireAtPlayer()
{
    if (ProjectileClass)
    {
        // Obtén la posición del jugador
        ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
        if (PlayerCharacter)
        {
            FVector FireDirection = (PlayerCharacter->GetActorLocation() - GetActorLocation()).GetSafeNormal();
            FVector SpawnLocation = GetActorLocation() + FireDirection * 100.0f; // Ajusta la posición de spawn según sea necesario

            // Crea el proyectil
            AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, SpawnLocation, FireDirection.Rotation());
            if (Projectile)
            {
                Projectile->SetOwner(this); // Opcional: establece al enemigo como el propietario del proyectil
            }
        }
    }



}

