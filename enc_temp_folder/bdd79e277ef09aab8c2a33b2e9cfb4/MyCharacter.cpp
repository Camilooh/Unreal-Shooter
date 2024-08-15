// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "Projectile.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PlayerController.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
	// Configura la tasa de giro y mirada
	TurnRate = 20.f;
	LookUpRate = 20.f;

	// Crear un brazo de c�mara y configurar su longitud
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 150.f;

	
	CameraBoom->bUsePawnControlRotation = true;

	// Crear una c�mara y adjuntarla al brazo de la c�mara
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

}
// Llamado cuando el juego comienza o cuando se genera el personaje
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	//GetCharacterMovement()->bEnablePhysicsInteraction = false;
}

// Llamado cada cuadro
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Configurar la entrada del jugador
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Enlazar las entradas de movimiento
	PlayerInputComponent->BindAxis("MoveForward", this, &AMyCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyCharacter::MoveRight);

	// Enlazar las entradas de c�mara
	PlayerInputComponent->BindAxis("Turn", this, &AMyCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &AMyCharacter::LookUpAtRate);


	//Enlazar las el Fire Button
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AMyCharacter::Fire);
}

// Movimiento adelante/atr�s
void AMyCharacter::MoveForward(float Value)
{
	if (Controller != nullptr && Value != 0.0f)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// Direcci�n hacia adelante
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

// Movimiento derecha/izquierda
void AMyCharacter::MoveRight(float Value)
{
	if (Controller != nullptr && Value != 0.0f)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// Direcci�n hacia la derecha
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

// Girar el personaje
void AMyCharacter::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * TurnRate * GetWorld()->GetDeltaSeconds());
}

// Mirar hacia arriba/abajo
void AMyCharacter::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * LookUpRate * GetWorld()->GetDeltaSeconds());
}

void AMyCharacter::Fire()
{
	if (ProjectileClass)
	{
		// Obtener la ubicaci�n y rotaci�n del personaje
		FVector MuzzleLocation = GetActorLocation() + GetActorForwardVector() * 100.0f; // Desplazar la ubicaci�n del proyectil hacia adelante
		FRotator MuzzleRotation = GetActorRotation(); // Rotaci�n del personaje

		// Par�metros de spawn
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = GetInstigator();

		// Spawnear el proyectil en la ubicaci�n del personaje
		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
		if (Projectile)
		{
			// Establecer la direcci�n inicial del proyectil
			FVector LaunchDirection = MuzzleRotation.Vector();
			Projectile->FireInDirection(LaunchDirection);
		}
	}
}


