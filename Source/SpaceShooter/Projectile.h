#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class SPACESHOOTER_API AProjectile : public AActor
{
	GENERATED_BODY()
    
public:    
	AProjectile();

protected:
	virtual void BeginPlay() override;

public:    
	virtual void Tick(float DeltaTime) override;

	// Composant de collision
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UBoxComponent* CollisionComp;

	// Sprite visuel du projectile
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UPaperSpriteComponent* ProjectileSprite;

	// Vitesse du tir
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float Speed;
};