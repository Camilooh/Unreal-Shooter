#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "MyCharacter.h"

AProjectile::AProjectile()
{
    PrimaryActorTick.bCanEverTick = true;

    // Crear el componente de colisión
    CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
    CollisionComp->InitSphereRadius(5.0f);
    CollisionComp->SetCollisionProfileName("Projectile");

    // Ignorar colisiones con el jugador
    CollisionComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
   

    CollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    CollisionComp->SetCollisionResponseToAllChannels(ECR_Block);

    RootComponent = CollisionComp;

    // Crear el componente de malla
    ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
    ProjectileMesh->SetupAttachment(RootComponent);

    // Configurar la malla
    static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Engine/BasicShapes/Sphere"));
    if (MeshAsset.Succeeded())
    {
        ProjectileMesh->SetStaticMesh(MeshAsset.Object);
        ProjectileMesh->SetRelativeScale3D(FVector(0.5f)); // Ajustar el tamaño si es necesario
    }

    // Crear el componente de movimiento del proyectil
    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
    ProjectileMovement->UpdatedComponent = CollisionComp;
    ProjectileMovement->InitialSpeed = 3000.0f;
    ProjectileMovement->MaxSpeed = 3000.0f;
    ProjectileMovement->bRotationFollowsVelocity = true;
    ProjectileMovement->bShouldBounce = false;
    ProjectileMovement->ProjectileGravityScale = 1.0f;

    // Manejar colisiones
    CollisionComp->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}


void AProjectile::BeginPlay()
{
    Super::BeginPlay();
}

void AProjectile::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    if (OtherActor && (OtherActor != this) && OtherComp)
    {
        AMyCharacter* Player = Cast<AMyCharacter>(OtherActor);
        if (Player)
        {
            Player->TakeDamage(10.0f);
        }
        else
        {
            OtherActor->Destroy();
        }

        // Destruye el proyectil después de aplicar el daño o si choca con cualquier otro objeto
        Destroy();
    }
}

void AProjectile::FireInDirection(const FVector& ShootDirection)
{
    if (ProjectileMovement)
    {
        ProjectileMovement->Velocity = ShootDirection * ProjectileMovement->InitialSpeed;
    }
}
