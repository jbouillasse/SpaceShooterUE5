#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaperFlipbookComponent.h"
#include "Asteroid.generated.h"

UCLASS()
class SPACESHOOTER_API AAsteroid : public AActor
{
	GENERATED_BODY()
    
public:	
	AAsteroid();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float MoveSpeed = 200.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Asteroid Stats")
	int32 MinHits = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Asteroid Stats")
	int32 MaxHits = 3;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	USoundBase* ExplosionSound;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visuals")
	class UPaperFlipbook* ExplosionFlipbook;

	int32 CurrentHits;

	// Fonction déclenchée lors d'une collision
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

private:
	FVector MovementDirection;
};