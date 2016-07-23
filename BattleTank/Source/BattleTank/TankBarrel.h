// Ben Paolillo - Copyright 2016

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
	public:
		void Elevate(float degreesPerSecond);

	private:
		
};
