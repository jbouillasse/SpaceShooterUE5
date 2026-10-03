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
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UFloatingPawnMovement* MovementComponent;

	void MoveRight(float Value);
	void MoveUp(float Value);
	void Shoot(); // Fonction de tir

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MoveSpeed = 600.0f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay")
	TSubclassOf<class AProjectile> ProjectileClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
	int32 Lives = 3;
	
	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
	void OnLifeChanged(int32 CurrentLives);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
	int32 Score = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
	int32 ScoreMultiplier = 1;
	
	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
	void OnScoreChanged(int32 NewScore, int32 CurrentMultiplier);
	
	void AddScore(int32 Points);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<class UUserWidget> GameOverWidgetClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	USoundBase* LaserSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	USoundBase* GameOverSound;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	USoundBase* HitSound;

	void LoseLife();
};