

#include "SpeedReductionZone.h"
#include "Components/BoxComponent.h"
#include "MyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/Engine.h"

// Sets default values
ASpeedReductionZone::ASpeedReductionZone()
{
    // Crear el componente de colisión
    CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent"));
    RootComponent = CollisionComponent;

    CollisionComponent->SetBoxExtent(FVector(200.f, 200.f, 50.f));
    CollisionComponent->SetCollisionProfileName(TEXT("Trigger"));
    CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ASpeedReductionZone::OnPlayerEnterZone);
    CollisionComponent->OnComponentEndOverlap.AddDynamic(this, &ASpeedReductionZone::OnPlayerExitZone);

    bIsPlayerInside = false;
}

// Called when the game starts or when spawned
void ASpeedReductionZone::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void ASpeedReductionZone::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
  
}

void ASpeedReductionZone::OnPlayerEnterZone(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (!bIsPlayerInside)
    {
        AMyCharacter* Character = Cast<AMyCharacter>(OtherActor);
        if (Character)
        {
            UCharacterMovementComponent* MovementComponent = Character->GetCharacterMovement();
            if (MovementComponent)
            {
                OriginalSpeed = MovementComponent->MaxWalkSpeed; // Guardar la velocidad original
                MovementComponent->MaxWalkSpeed *= ReducedSpeedMultiplier;

                // Mensaje de depuración en el log
                UE_LOG(LogTemp, Warning, TEXT("Player entered speed reduction zone. Speed reduced to %f"), MovementComponent->MaxWalkSpeed);

                // Mensaje de depuración en pantalla
                if (GEngine)
                {
                    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Entered Speed Reduction Zone"));
                }

                bIsPlayerInside = true; // Marcar como dentro de la zona
            }
        }
    }
}

void ASpeedReductionZone::OnPlayerExitZone(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (bIsPlayerInside)
    {
        AMyCharacter* Character = Cast<AMyCharacter>(OtherActor);
        if (Character)
        {
            UCharacterMovementComponent* MovementComponent = Character->GetCharacterMovement();
            if (MovementComponent)
            {
                MovementComponent->MaxWalkSpeed = OriginalSpeed; // Restaurar la velocidad original

                // Mensaje de depuración en el log
                UE_LOG(LogTemp, Warning, TEXT("Player exited speed reduction zone. Speed restored to %f"), MovementComponent->MaxWalkSpeed);

                // Mensaje de depuración en pantalla
                if (GEngine)
                {
                    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Exited Speed Reduction Zone"));
                }

                bIsPlayerInside = false; // Marcar como fuera de la zona
            }
        }
    }
}
