// Ben Paolillo - Copyright 2016

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS( meta = (BlueprintSpawnableComponent) )
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
	public:
		// -1 is max downward speed, +1 is max upward speed
		void Elevate(float relativeSpeed);

	private:
		UPROPERTY(EditAnywhere, Category = Setup)
		float m_MaxDegreesPerSecond = 20;

		UPROPERTY(EditAnywhere, Category = Setup)
		float m_MaxElevationDegrees = 40;

		UPROPERTY(EditAnywhere, Category = Setup)
		float m_MinElevationDegrees = 0;
};
