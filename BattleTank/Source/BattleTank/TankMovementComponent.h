// Ben Paolillo - Copyright 2016

#pragma once

#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;

/**
 * Responsible for driving the tank tracks.
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
	public:
		UFUNCTION(BlueprintCallable, Category = "Setup")
		void Initialize(UTankTrack* leftTrackToSet, UTankTrack* rightTrackToSet);

		UFUNCTION(BlueprintCallable, Category = "Input")
		void IntendMoveForward(float input);

		UFUNCTION(BlueprintCallable, Category = "Input")
		void IntendTurnRight(float input);

	private:
		UTankTrack* m_LeftTrack = nullptr;
		UTankTrack* m_RightTrack = nullptr;

		// Called from the pathfinding logic by the AI controllers
		virtual void RequestDirectMove(const FVector& moveVelocity, bool forceMaxSpeed) override;
};
