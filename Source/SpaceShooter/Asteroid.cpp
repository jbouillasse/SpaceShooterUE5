#include "Asteroid.h"
#include "Kismet/GameplayStatics.h"
#include "SpaceshipPawn.h"
#include "Projectile.h"
#include "Sound/SoundBase.h"
#include "PaperFlipbookActor.h"
#include "PaperFlipbook.h"

AAsteroid::AAsteroid()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AAsteroid::BeginPlay()
{
	Super::BeginPlay();
	CurrentHits = FMath::RandRange(MinHits, MaxHits);
	AActor* Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    
	if (Player)
	{
		MovementDirection = Player->GetActorLocation() - GetActorLocation();
		MovementDirection.Normalize();
		MovementDirection.X += FMath::RandRange(-0.3f, 0.3f);
		MovementDirection.Z += FMath::RandRange(-0.3f, 0.3f);
		MovementDirection.Normalize();
	}
	else
	{
		MovementDirection = FVector(0.0f, 0.0f, -1.0f);
	}
}

void AAsteroid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector DeltaMovement = MovementDirection * MoveSpeed * DeltaTime;
	AddActorWorldOffset(DeltaMovement, true);
}

void AAsteroid::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (!OtherActor || OtherActor == this) return;

	//L'astéroïde touche un projectile
	if (AProjectile* Laser = Cast<AProjectile>(OtherActor))
	{
		Laser->Destroy(); 
		CurrentHits--;    

		if (CurrentHits <= 0)
		{
			// Fait apparaître un acteur d'animation indépendant dans le monde
			if (ExplosionFlipbook)
			{
				APaperFlipbookActor* ExplosionActor = GetWorld()->SpawnActor<APaperFlipbookActor>(GetActorLocation(), FRotator::ZeroRotator);
				if (ExplosionActor && ExplosionActor->GetRenderComponent())
				{
					ExplosionActor->GetRenderComponent()->SetFlipbook(ExplosionFlipbook);
					ExplosionActor->GetRenderComponent()->SetLooping(false);
                
					// L'acteur d'explosion se détruira tout seul exactement à la fin de l'animation
					ExplosionActor->SetLifeSpan(ExplosionFlipbook->GetTotalDuration());
				}
			}

			ASpaceshipPawn* Player = Cast<ASpaceshipPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
			if (Player)
			{
				Player->AddScore(10);
			}

			if (ExplosionSound)
			{
				UGameplayStatics::PlaySoundAtLocation(GetWorld(), ExplosionSound, GetActorLocation(), 1.0f);
			}

			Destroy(); 
		}
	}
	//L'astéroïde touche le vaisseau du joueur
	else if (ASpaceshipPawn* Player = Cast<ASpaceshipPawn>(OtherActor))
	{
		Player->LoseLife(); 
		Destroy();          
	}
}