// Ben Paolillo - Copyright 2016

#pragma once

#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
	protected:
		// How close the AI tank can get to the player tank
		UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float AcceptanceRadius = 8000.0f;

	private:
		virtual void BeginPlay() override;

		virtual void Tick(float deltaSeconds) override;

		virtual void SetPawn(APawn* inPawn) override;

		UFUNCTION()
		void OnTankDeath();
};
