// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/PlayerHUD.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
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

        // Verifica si la creación del widget fue exitosa
        if (HUDWidget)
        {
            // Añade el widget al viewport
            HUDWidget->AddToViewport();
            

            // Actualiza el texto con la cantidad de enemigos inicial
            ExecuteEnemyFunc();
            UpdateAmmoCount();
            UpdateHealthBar();
            // Busca el botón del menú principal en el widget
          /* UButton* MainMenuButton = Cast<UButton>(HUDWidget->GetWidgetFromName(TEXT("MainMenuButton")));
            if (MainMenuButton)
            {
                MainMenuButton->OnClicked.AddDynamic(this, &APlayerHUD::OnMainMenuButtonClicked);
            }*/
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
    // Obtén una referencia al personaje del jugador
    AMyCharacter* MyCharacter = Cast<AMyCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));

    if (MyCharacter)
    {
        // Obtén el valor de la munición del personaje
        int32 AmmoCount = MyCharacter->GetAmmo(); // Asumiendo que tienes una función GetAmmo()

        // Encuentra el texto en el HUD y actualízalo
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
void APlayerHUD::ExecuteEnemyFunc() 
{
    FTimerHandle TimerHandle;

    // Configura el temporizador para ejecutar la función después de 2 segundos
    GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &APlayerHUD::UpdateEnemyCount, 2.0f, false);
}
void APlayerHUD::UpdateEnemyCount()
{
    // AGREGAR UN PEQUEÑO DELAY ANTES DE CARGAR ESTO 
    // Obtén todos los actores de tipo EnemyActor en el nivel
    TArray<AActor*> EnemyActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyActor::StaticClass(), EnemyActors);

    // Cuenta la cantidad de enemigos
    int32 EnemyCount = EnemyActors.Num();

    // Encuentra el texto en el HUD y actualízalo
    if (HUDWidget)
    {
        UTextBlock* EnemyCountText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("EnemiesCountText")));
        if (EnemyCountText)
        {
            EnemyCountText->SetText(FText::AsNumber(EnemyCount));
        }
    }

    if(EnemyCount <= 0)
    {
        ShowWinScreen();
    
    }
}
void APlayerHUD::UpdateHealthBar()
{
    // Obtén una referencia al personaje del jugador
    AMyCharacter* MyCharacter = Cast<AMyCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));

    if (MyCharacter)
    {
        // Obtén el porcentaje de salud del personaje
        float HealthPercent = MyCharacter->GetHealth() / MyCharacter->MaxHealth;

        // Encuentra la barra de salud en el HUD y actualízala
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
            // Congelar el juego y mostrar el cursor del mouse
           APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
            if (PlayerController)
            {
                PlayerController->SetPause(true);
                PlayerController->bShowMouseCursor = true;
                PlayerController->SetInputMode(FInputModeUIOnly());
            }
        }
        // Buscar y configurar el botón del menú principal en el Win Screen
        UButton* MainMenuButton = Cast<UButton>(HUDWidget->GetWidgetFromName(TEXT("MainMenuButton1")));
        if (MainMenuButton)
        {
            MainMenuButton->OnClicked.AddDynamic(this, &APlayerHUD::OnMainMenuButtonClicked);
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

        // Congelar el juego estableciendo la tasa de tiempo a 0
        UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.0f);

        // Mostrar el cursor del mouse
        APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
        if (PlayerController)
        {
            PlayerController->bShowMouseCursor = true;
            PlayerController->SetInputMode(FInputModeUIOnly());
        }

        // Buscar y configurar el botón del menú principal en el Lose Screen
        UButton* MainMenuButton = Cast<UButton>(HUDWidget->GetWidgetFromName(TEXT("MainMenuButton")));
        if (MainMenuButton)
        {
            MainMenuButton->OnClicked.AddDynamic(this, &APlayerHUD::OnMainMenuButtonClicked);
        }
    }
}
void APlayerHUD::OnMainMenuButtonClicked()
{
    // Aquí agregas la lógica para llevar al jugador al menú principal
    UGameplayStatics::OpenLevel(this, FName("MainMenu"));
}


