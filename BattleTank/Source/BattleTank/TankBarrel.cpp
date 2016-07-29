// Ben Paolillo - Copyright 2016

#include "BattleTank.h"
#include "TankBarrel.h"

void UTankBarrel::Elevate(float relativeSpeed)
{
	// Move the barrel the right amount this frame given a max elevation speed
	// and frame time
	relativeSpeed = FMath::Clamp(relativeSpeed, -1.0f, 1.0f);

	float elevationChange = relativeSpeed * m_MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float rawNewElevation = RelativeRotation.Pitch + elevationChange;
	float clampedNewElevation = FMath::Clamp(rawNewElevation, m_MinElevationDegrees, m_MaxElevationDegrees);

	SetRelativeRotation(FRotator(clampedNewElevation, 0, 0));
}


