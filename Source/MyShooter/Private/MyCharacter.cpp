// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "Projectile.h"
#include "HUD/PlayerHUD.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PlayerController.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
	//Health 
	MaxHealth = 100.0f;
	Health = MaxHealth;

	//Ammo
	Ammo = 10;

	// Configura la tasa de giro y mirada
	TurnRate = 20.f;
	LookUpRate = 20.f;

	// Crear un brazo de cámara y configurar su longitud
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 150.f;

	
	CameraBoom->bUsePawnControlRotation = true;

	// Crear una cámara y adjuntarla al brazo de la cámara
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

}

void AMyCharacter::TakeDamage(float DamageAmount)
{
	Health -= DamageAmount;
	if (Health <= 0)
	{
		// Obtener el PlayerController
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		if (PlayerController)
		{
			// Obtener el HUD y llamar a ShowLoseScreen
			APlayerHUD* PlayerHUD = Cast<APlayerHUD>(PlayerController->GetHUD());
			if (PlayerHUD)
			{
				PlayerHUD->ShowLoseScreen();
			}
		}
	}
}
float AMyCharacter::GetHealth() const
{
	return Health;
}
void AMyCharacter::AddHealth(int32 Amount)
{

	Health += Amount;
}
int32 AMyCharacter::GetAmmo() const
{
	return Ammo;
}

void AMyCharacter::AddAmmo(int32 Amount)
{
	Ammo += Amount;
	// Aquí puedes añadir lógica adicional si es necesario, como actualizaciones en el HUD
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

	// Enlazar las entradas de cámara
	PlayerInputComponent->BindAxis("Turn", this, &AMyCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &AMyCharacter::LookUpAtRate);


	//Enlazar las el Fire Button
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AMyCharacter::Fire);
}

// Movimiento adelante/atrás
void AMyCharacter::MoveForward(float Value)
{
	if (Controller != nullptr && Value != 0.0f)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// Dirección hacia adelante
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

		// Dirección hacia la derecha
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
	if (Ammo > 0 && ProjectileClass)
	{
		// Disparar el proyectil si hay munición disponible
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		if (PlayerController)
		{
			int32 ViewportSizeX, ViewportSizeY;
			PlayerController->GetViewportSize(ViewportSizeX, ViewportSizeY);

			FVector CrosshairLocation;
			FVector CrosshairDirection;
			if (PlayerController->DeprojectScreenPositionToWorld(ViewportSizeX / 2.0f, ViewportSizeY / 2.0f, CrosshairLocation, CrosshairDirection))
			{
				FVector MuzzleLocation = GetActorLocation() + GetActorForwardVector() * 100.0f;
				FRotator MuzzleRotation = CrosshairDirection.Rotation();

				FActorSpawnParameters SpawnParams;
				SpawnParams.Owner = this;
				SpawnParams.Instigator = GetInstigator();

				AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
				if (Projectile)
				{
					Projectile->FireInDirection(CrosshairDirection);

					// Reducir la munición en 1 después de disparar
					Ammo--;
				}
			}
		}
	}
}





