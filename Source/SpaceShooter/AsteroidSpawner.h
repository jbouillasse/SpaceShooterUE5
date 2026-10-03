#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AsteroidSpawner.generated.h"

UCLASS()
class SPACESHOOTER_API AAsteroidSpawner : public AActor
{
	GENERATED_BODY()
    
public:    
	AAsteroidSpawner();

protected:
	virtual void BeginPlay() override;

public:    
	// Classe de l'astéroïde à faire apparaître
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	TSubclassOf<AActor> AsteroidClass;

	// Temps minimum entre deux apparitions
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	float MinSpawnDelay;

	// Temps maximum entre deux apparitions
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	float MaxSpawnDelay;

	// Limites de la zone d'apparition
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	FVector2D SpawnAreaMin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	FVector2D SpawnAreaMax;
	
	// La valeur retirée aux délais à chaque apparition
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Difficulty")
	float DecreaseAmount = 0.05f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Difficulty")
	float AbsoluteMinDelay = 0.3f;

private:
	FTimerHandle SpawnTimerHandle;
	void SpawnAsteroid();
};