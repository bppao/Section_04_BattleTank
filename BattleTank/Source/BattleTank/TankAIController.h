// Ben Paolillo - Copyright 2016

#pragma once

#include "AIController.h"
#include "TankAIController.generated.h"

class ATank; // Forward declaration

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
	private:
		virtual void BeginPlay() override;

		virtual void Tick(float deltaSeconds) override;

		ATank* GetControlledTank() const;

		ATank* GetPlayerTank() const;

		ATank* m_PlayerTank;
};
