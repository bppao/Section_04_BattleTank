// Ben Paolillo - Copyright 2016

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * TankTrack is used to set maximum driving force and to apply forces to the tank.
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
	public:
		UTankTrack();

		// Sets a throttle between -1 and +1
		UFUNCTION(BlueprintCallable, Category = "Input")
		void SetThrottle(float throttle);

		void DriveTrack();

		// Max force per track in Newtons
		UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float TrackMaxDrivingForce = 400000.0f; // Assume 40,000 kg tank and 1g acceleration

	private:
		virtual void BeginPlay() override;

		void ApplySidewaysForce();

		UFUNCTION()
		void OnHit(UPrimitiveComponent* hitComponent, AActor* otherActor, UPrimitiveComponent* otherComp, FVector normalImpulse, const FHitResult& hit);

		float m_CurrentThrottle = 0.0f;
};
