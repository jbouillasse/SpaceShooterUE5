#include "Projectile.h"
#include "Components/BoxComponent.h"
#include "PaperSpriteComponent.h"

void AProjectile::BeginPlay()
{
    Super::BeginPlay();
}

AProjectile::AProjectile()
{
    PrimaryActorTick.bCanEverTick = true;

    // Collision du projectile
    CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComp"));
    RootComponent = CollisionComp;
    CollisionComp->SetBoxExtent(FVector(10.0f, 10.0f, 10.0f));

    // Sprite visuel du projectile
    ProjectileSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("ProjectileSprite"));
    ProjectileSprite->SetupAttachment(RootComponent);

    // Vitesse du projectile
    Speed = 800.0f;
}

void AProjectile::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    FVector NewLocation = GetActorLocation() + (FVector(0.0f, 0.0f, 1.0f) * Speed * DeltaTime);
    SetActorLocation(NewLocation);
}