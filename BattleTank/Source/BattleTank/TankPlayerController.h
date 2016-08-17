// Ben Paolillo - Copyright 2016

#pragma once

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" // NOTE: Must be last include

class UTankAimingComponent; // Forward declaration

/**
 * Player controller for the tank.
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	protected:
		// NOTE: Because of this special Unreal macro, we don't even
		// need to implement this function!
		UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
		void FoundAimingComponent(UTankAimingComponent* aimingCompRef);

	private:
		UPROPERTY(EditDefaultsOnly)
		float m_CrosshairXLocation = 0.5f;

		UPROPERTY(EditDefaultsOnly)
		float m_CrosshairYLocation = 0.33333f;

		UPROPERTY(EditDefaultsOnly)
		float m_LineTraceRange = 1000000.0f;

		virtual void BeginPlay() override;

		virtual void Tick(float deltaSeconds) override;

		virtual void SetPawn(APawn* inPawn) override;

		// Start the tank moving the barrel so that a shot would hit where
		// the crosshair intersects with the world
		void AimTowardsCrosshair();

		// Return an OUT parameter, true if hit landscape
		bool GetSightRayHitLocation(FVector &hitLocation) const;

		bool GetLookVectorHitLocation(FVector lookDirection, FVector &hitLocation) const;

		bool GetLookDirection(FVector2D screenLocation, FVector &lookDirection) const;

		UFUNCTION()
		void OnTankDeath();
};
