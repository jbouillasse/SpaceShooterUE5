#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SpaceshipPawn.generated.h"

UCLASS()
class SPACESHOOTER_API ASpaceshipPawn : public APawn
{
	GENERATED_BODY()

public:
	ASpaceshipPawn();

protected:
	virtual void BeginPlay() override;

public:    
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UBoxComponent* CollisionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UPaperSpriteComponent* ShipSpriteComponent;

	void MoveRight(float Value);
	void MoveUp(float Value);
	void Shoot(); // Fonction de tir

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MoveSpeed = 600.0f;

	// Référence de la classe du projectile à assigner dans le Blueprint
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay")
	TSubclassOf<class AProjectile> ProjectileClass;

private:
	FVector CurrentVelocity;
};