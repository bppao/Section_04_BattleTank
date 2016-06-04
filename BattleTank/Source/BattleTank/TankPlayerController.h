// Ben Paolillo - Copyright 2016

#pragma once

#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" // NOTE: Must be last include

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	public:
		virtual void BeginPlay() override;

		virtual void Tick(float deltaSeconds) override;

		ATank* GetControlledTank() const;

	private:
		// Start the tank moving the barrel so that a shot would hit where
		// the crosshair intersects with the world
		void AimTowardsCrosshair();
};
