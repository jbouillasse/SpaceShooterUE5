#include "SpaceshipPawn.h"
#include "Components/BoxComponent.h"
#include "PaperSpriteComponent.h"
#include "Projectile.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"
#include "GameFramework/PlayerController.h"

ASpaceshipPawn::ASpaceshipPawn()
{
    // On désactive le Tick car le mouvement est géré par le composant
    PrimaryActorTick.bCanEverTick = false;

    // Initialisation du composant de mouvement natif
    MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComponent"));
    MovementComponent->MaxSpeed = MoveSpeed;
}

void ASpaceshipPawn::BeginPlay()
{
    Super::BeginPlay();
    
    // Assure que la vitesse définie dans le Blueprint est bien appliquée au lancement
    if (MovementComponent)
    {
        MovementComponent->MaxSpeed = MoveSpeed;
    }
}

void ASpaceshipPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("MoveRight", this, &ASpaceshipPawn::MoveRight);
    PlayerInputComponent->BindAxis("MoveUp", this, &ASpaceshipPawn::MoveUp);
    PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &ASpaceshipPawn::Shoot);
}

void ASpaceshipPawn::Shoot()
{
    if (ProjectileClass)
    {
        FVector SpawnLocation = GetActorLocation() + FVector(1.5, 0.0f, 0.0f); 
        FRotator SpawnRotation = FRotator::ZeroRotator;
        GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnLocation, SpawnRotation);
        
        //Volume
        if (LaserSound)
        {
            UGameplayStatics::PlaySound2D(GetWorld(), LaserSound, 0.05f);
        }
    }
}

void ASpaceshipPawn::LoseLife()
{
    Lives--;
    ScoreMultiplier = 1;
    
    OnLifeChanged(Lives);
    OnScoreChanged(Score, ScoreMultiplier);
    
    if (Lives <= 0)
    {
        if (GameOverSound)
        {
            UGameplayStatics::PlaySound2D(GetWorld(), GameOverSound, 0.6f);
        }

        if (GameOverWidgetClass)
        {
            UUserWidget* GameOverWidget = CreateWidget<UUserWidget>(GetWorld(), GameOverWidgetClass);
            if (GameOverWidget)
            {
                GameOverWidget->AddToViewport();
                
                APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
                if (PC)
                {
                    // On paramètre le mode de contrôle uniquement sur l'UI
                    FInputModeUIOnly InputModeData;
                    InputModeData.SetWidgetToFocus(GameOverWidget->TakeWidget());
                    InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
                    
                    PC->SetInputMode(InputModeData);
                    PC->bShowMouseCursor = true; // On force l'affichage de la souris
                }
            }
        }

        Destroy(); 
    }
    else 
    {
        if (HitSound)
        {
            UGameplayStatics::PlaySound2D(GetWorld(), HitSound, 1.0f);
        }
    }
}

void ASpaceshipPawn::MoveRight(float Value)
{
    if (Value != 0.0f)
    {
        AddMovementInput(FVector(1.0f, 0.0f, 0.0f), Value);
    }
}

void ASpaceshipPawn::MoveUp(float Value)
{
    if (Value != 0.0f)
    {
        AddMovementInput(FVector(0.0f, 0.0f, 1.0f), Value);
    }
}

void ASpaceshipPawn::AddScore(int32 Points)
{
    Score += (Points * ScoreMultiplier);
    ScoreMultiplier++; 
    OnScoreChanged(Score, ScoreMultiplier);
}
