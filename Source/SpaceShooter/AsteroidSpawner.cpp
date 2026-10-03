#include "AsteroidSpawner.h"
#include "TimerManager.h"
#include "Math/UnrealMathUtility.h"

AAsteroidSpawner::AAsteroidSpawner()
{
    PrimaryActorTick.bCanEverTick = false;
    
    MinSpawnDelay = 1.0f;
    MaxSpawnDelay = 3.0f;
    
    SpawnAreaMin = FVector2D(-680.0f, 400.0f); 
    SpawnAreaMax = FVector2D(60.0f, 700.0f);
}

void AAsteroidSpawner::BeginPlay()
{
    Super::BeginPlay();

    // Lancement du premier timer avec un délai aléatoire
    float FirstDelay = FMath::RandRange(MinSpawnDelay, MaxSpawnDelay);
    GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &AAsteroidSpawner::SpawnAsteroid, FirstDelay, false);
}


    void AAsteroidSpawner::SpawnAsteroid()
    {
        {
            if (AsteroidClass)
            {
                // On récupère la position du spawner
                FVector SpawnLocation = GetActorLocation(); 

                // Choisit un bord aléatoire
                int32 Edge = FMath::RandRange(0, 3);

                if (Edge == 0) // Haut
                {
                    SpawnLocation.X = FMath::RandRange(SpawnAreaMin.X, SpawnAreaMax.X);
                    SpawnLocation.Z = SpawnAreaMax.Y; 
                }
                else if (Edge == 1) // Bas
                {
                    SpawnLocation.X = FMath::RandRange(SpawnAreaMin.X, SpawnAreaMax.X);
                    SpawnLocation.Z = SpawnAreaMin.Y;
                }
                else if (Edge == 2) // Gauche
                {
                    SpawnLocation.X = SpawnAreaMin.X;
                    SpawnLocation.Z = FMath::RandRange(SpawnAreaMin.Y, SpawnAreaMax.Y);
                }
                else // Droite
                {
                    SpawnLocation.X = SpawnAreaMax.X;
                    SpawnLocation.Z = FMath::RandRange(SpawnAreaMin.Y, SpawnAreaMax.Y);
                }

                // Fait apparaître l'astéroïde
                GetWorld()->SpawnActor<AActor>(AsteroidClass, SpawnLocation, FRotator::ZeroRotator);
            }
    
            // On réduit les limites de temps
            MinSpawnDelay = FMath::Max(AbsoluteMinDelay, MinSpawnDelay - DecreaseAmount);
            MaxSpawnDelay = FMath::Max(AbsoluteMinDelay + 0.5f, MaxSpawnDelay - DecreaseAmount); 
            // Relance le timer pour le prochain astéroïde avec les nouveaux délais réduits
            float NextDelay = FMath::RandRange(MinSpawnDelay, MaxSpawnDelay);
            GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &AAsteroidSpawner::SpawnAsteroid, NextDelay, false);
        }
}