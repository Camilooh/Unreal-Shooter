// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Projectile.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "TimerManager.h"


// Sets default values
AEnemyActor::AEnemyActor()
{
    PrimaryActorTick.bCanEverTick = true;

    // En el constructor de la clase
    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    MeshComponent->SetSimulatePhysics(false);  // Desactivar la f�sica si no quieres que la gravedad afecte
    MeshComponent->SetEnableGravity(false);    // Desactivar la gravedad
    MeshComponent->BodyInstance.bLockZTranslation = true;
    MeshComponent->SetCollisionProfileName(TEXT("BlockAll")); // Configura la colisi�n para bloquear todo
    RootComponent = MeshComponent;

    // Configura la colisi�n del MeshComponent
   /* MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    MeshComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
    MeshComponent->SetCollisionResponseToChannel(ECC_WorldStatic, ECollisionResponse::ECR_Block);
    MeshComponent->SetCollisionResponseToChannel(ECC_WorldDynamic, ECollisionResponse::ECR_Block);*/

    // Configura la f�sica
    
   

    DetectionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("DetectionSphere"));
    DetectionSphere->SetupAttachment(RootComponent);
    DetectionSphere->InitSphereRadius(500.0f); // Ajusta el radio de detecci�n seg�n sea necesario
    DetectionSphere->OnComponentBeginOverlap.AddDynamic(this, &AEnemyActor::OnDetectionSphereOverlap);
    DetectionSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    DetectionSphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
}

// Called when the game starts or when spawned
void AEnemyActor::BeginPlay()
{
    Super::BeginPlay();
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Enemigo"));
    }

    // Inicializa la direcci�n de movimiento aleatorio
    MoveRandomly();

    // Establece un temporizador para cambiar la direcci�n aleatoria
    GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AEnemyActor::MoveRandomly, ChangeDirectionInterval, true);
    GetWorld()->GetTimerManager().SetTimer(FireTimerHandle, this, &AEnemyActor::FireAtPlayer, 2.0f, true);
}

// Called every frame
void AEnemyActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Mueve al enemigo en la direcci�n actual calculada en MoveRandomly
    FVector NewLocation = GetActorLocation() + (CurrentDirection * MovementSpeed * DeltaTime);

    // Mantener la altura original del enemigo
    NewLocation.Z = GetActorLocation().Z;

    // Mover al enemigo a la nueva ubicaci�n
    SetActorLocation(NewLocation);
}

void AEnemyActor::OnDetectionSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)

{
    if (OtherActor && OtherActor != this && OtherActor->IsA(ACharacter::StaticClass())) // Verifica si es el jugador
    {
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Player enter zone"));
        }
        FireAtPlayer();
    }

}


void AEnemyActor::FireAtPlayer()
{
    if (ProjectileClass)
    {
        // Obt�n la posici�n del jugador
        ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
        if (PlayerCharacter)
        {
            if (GEngine)
            {
                GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("ShootPlayer"));
            }
            FVector FireDirection = (PlayerCharacter->GetActorLocation() - GetActorLocation()).GetSafeNormal();
            FVector SpawnLocation = GetActorLocation() + FireDirection * 100.0f; // Ajusta la posici�n de spawn seg�n sea necesario

            // Crea el proyectil
            AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, SpawnLocation, FireDirection.Rotation());
            if (Projectile)
            {
                Projectile->SetOwner(this); // Opcional: establece al enemigo como el propietario del proyectil
            }
        }
    }
    else {
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, TEXT("No Projectile Class"));
        }
    }



}

void AEnemyActor::MoveRandomly()
{
    // Generar una direcci�n aleatoria en el plano X-Y
    FVector RandomDirection = FVector(FMath::FRandRange(-1.0f, 1.0f), FMath::FRandRange(-1.0f, 1.0f), 0.0f);
    RandomDirection.Normalize();

    // Almacenar la direcci�n aleatoria en CurrentDirection
    CurrentDirection = RandomDirection;
}


