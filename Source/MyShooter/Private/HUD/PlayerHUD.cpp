// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/PlayerHUD.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "Enemy/EnemyActor.h"
#include "Components/TextBlock.h" 
#include "Components/ProgressBar.h"
#include "MyCharacter.h"


void APlayerHUD::BeginPlay()
{
    Super::BeginPlay();
   
    // Verifica si se ha asignado una clase de Widget Blueprint
    if (HUDWidgetClass)
    {
        // Crea una instancia del Widget Blueprint
        HUDWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);

        // Verifica si la creaci�n del widget fue exitosa
        if (HUDWidget)
        {
            // A�ade el widget al viewport
            HUDWidget->AddToViewport();
            

            // Actualiza el texto con la cantidad de enemigos inicial
            UpdateEnemyCount();
            UpdateAmmoCount();
            UpdateHealthBar();
        }
    }

    // Configura los bindings para las teclas
    if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0))
    {
        PlayerController->InputComponent->BindAction("ShowWinScreen", IE_Pressed, this, &APlayerHUD::ShowWinScreen);
        PlayerController->InputComponent->BindAction("ShowLoseScreen", IE_Pressed, this, &APlayerHUD::ShowLoseScreen);
    }

}

void APlayerHUD::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

   
    UpdateAmmoCount();
    UpdateEnemyCount();
    UpdateHealthBar();
}
void APlayerHUD::UpdateAmmoCount()
{
    // Obt�n una referencia al personaje del jugador
    AMyCharacter* MyCharacter = Cast<AMyCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));

    if (MyCharacter)
    {
        // Obt�n el valor de la munici�n del personaje
        int32 AmmoCount = MyCharacter->GetAmmo(); // Asumiendo que tienes una funci�n GetAmmo()

        // Encuentra el texto en el HUD y actual�zalo
        if (HUDWidget)
        {
            UTextBlock* AmmoCountText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("AmmoCountText")));
            if (AmmoCountText)
            {
                AmmoCountText->SetText(FText::AsNumber(AmmoCount));
            }
        }
    }
}
void APlayerHUD::UpdateEnemyCount()
{
    // Obt�n todos los actores de tipo EnemyActor en el nivel
    TArray<AActor*> EnemyActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyActor::StaticClass(), EnemyActors);

    // Cuenta la cantidad de enemigos
    int32 EnemyCount = EnemyActors.Num();

    // Encuentra el texto en el HUD y actual�zalo
    if (HUDWidget)
    {
        UTextBlock* EnemyCountText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("EnemiesCountText")));
        if (EnemyCountText)
        {
            EnemyCountText->SetText(FText::AsNumber(EnemyCount));
        }
    }
}
void APlayerHUD::UpdateHealthBar()
{
    // Obt�n una referencia al personaje del jugador
    AMyCharacter* MyCharacter = Cast<AMyCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));

    if (MyCharacter)
    {
        // Obt�n el porcentaje de salud del personaje
        float HealthPercent = MyCharacter->GetHealth() / MyCharacter->MaxHealth;

        // Encuentra la barra de salud en el HUD y actual�zala
        if (HUDWidget)
        {
            UProgressBar* HealthProgressBar = Cast<UProgressBar>(HUDWidget->GetWidgetFromName(TEXT("HealthProgressBar")));
            if (HealthProgressBar)
            {
                HealthProgressBar->SetPercent(HealthPercent);
            }
        }
    }
}
void APlayerHUD::ShowWinScreen()
{
    if (HUDWidget)
    {
       
        // Mostrar el elemento de Win Screen
        UWidget* WinScreenWidget = HUDWidget->GetWidgetFromName(TEXT("WinScreenElement"));
        if (WinScreenWidget)
        {
           
            WinScreenWidget->SetVisibility(ESlateVisibility::Visible);
        }
    }
    else
    {
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Se agrego el widget"));
        }
    }
}

void APlayerHUD::ShowLoseScreen()
{
    if (HUDWidget)
    {
        // Mostrar el elemento de Lose Screen
        UWidget* LoseScreenWidget = HUDWidget->GetWidgetFromName(TEXT("LoseScreenElement"));
        if (LoseScreenWidget)
        {
            LoseScreenWidget->SetVisibility(ESlateVisibility::Visible);
        }
    }
}


