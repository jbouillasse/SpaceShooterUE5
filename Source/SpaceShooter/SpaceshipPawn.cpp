#include "SpaceshipPawn.h"
#include "Components/BoxComponent.h"
#include "PaperSpriteComponent.h"
#include "Projectile.h"

ASpaceshipPawn::ASpaceshipPawn()
{
    PrimaryActorTick.bCanEverTick = true;

    // Boîte de collision principale
    CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent"));
    RootComponent = CollisionComponent;
    CollisionComponent->SetBoxExtent(FVector(20.0f, 30.0f, 30.0f));

    // Sprite du vaisseau
    ShipSpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("ShipSprite"));
    ShipSpriteComponent->SetupAttachment(RootComponent);
}

void ASpaceshipPawn::BeginPlay()
{
    Super::BeginPlay();
}

void ASpaceshipPawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!CurrentVelocity.IsZero())
    {
        FVector NewLocation = GetActorLocation() + (CurrentVelocity * DeltaTime);

        NewLocation.X = FMath::Clamp(NewLocation.X, -680.0f, 60.0f); 
        NewLocation.Z = FMath::Clamp(NewLocation.Z, 400.0f, 700.0f); 

        SetActorLocation(NewLocation, true);
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
        FVector SpawnLocation = GetActorLocation() + FVector(0.0f, 0.0f, -30.0f); 
        FRotator SpawnRotation = FRotator::ZeroRotator;
        GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnLocation, SpawnRotation);
    }
}

void ASpaceshipPawn::MoveRight(float Value)
{
    CurrentVelocity.X = Value * MoveSpeed;
}

void ASpaceshipPawn::MoveUp(float Value)
{
    CurrentVelocity.Z = Value * MoveSpeed;
}