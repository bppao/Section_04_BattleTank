// Ben Paolillo - Copyright 2016

#pragma once

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" // NOTE: Must be last include

class ATank; // Forward declaration

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	private:
		UPROPERTY(EditAnywhere)
		float m_CrosshairXLocation = 0.5f;

		UPROPERTY(EditAnywhere)
		float m_CrosshairYLocation = 0.33333f;

		UPROPERTY(EditAnywhere)
		float m_LineTraceRange = 1000000.0f;

		virtual void BeginPlay() override;

		virtual void Tick(float deltaSeconds) override;

		ATank* GetControlledTank() const;

		// Start the tank moving the barrel so that a shot would hit where
		// the crosshair intersects with the world
		void AimTowardsCrosshair();

		// Return an OUT parameter, true if hit landscape
		bool GetSightRayHitLocation(FVector &hitLocation) const;

		bool GetLookVectorHitLocation(FVector lookDirection, FVector &hitLocation) const;

		bool GetLookDirection(FVector2D screenLocation, FVector &lookDirection) const;
};
