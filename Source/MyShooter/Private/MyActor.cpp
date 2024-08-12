// MyActor.cpp
#include "MyActor.h"
#include "Engine/Engine.h"  // Incluye el encabezado necesario

// Sets default values
AMyActor::AMyActor()
{
    PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
    Super::BeginPlay();

    // Mostrar mensaje en pantalla en BeginPlay
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Hola"));
    }
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Mostrar mensaje en pantalla en Tick
    if (GEngine)
    {
        FString DebugMessage = FString::Printf(TEXT("AMyActor::Tick() llamado con DeltaTime: %f"), DeltaTime);
        GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Green, DebugMessage);
    }
}
