// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class MYSHOOTER_API AProjectile : public AActor
{
    GENERATED_BODY()

public:
    AProjectile();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    // Componente de colisión
    UPROPERTY(VisibleAnywhere, Category = "Components")
    class USphereComponent* CollisionComp;

    // Componente del proyectil
    UPROPERTY(VisibleAnywhere, Category = "Components")
    class UProjectileMovementComponent* ProjectileMovement;

    // Función para manejar el impacto
    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

    void FireInDirection(const FVector& ShootDirection);

    UPROPERTY(VisibleAnywhere, Category = "Components")
    class UStaticMeshComponent* ProjectileMesh;
};
