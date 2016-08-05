// Ben Paolillo - Copyright 2016

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()

	public:
		void Rotate(float relativeSpeed);

	private:
		UPROPERTY(EditAnywhere, Category = Setup)
		float m_MaxDegreesPerSecond = 20.0f;
};
