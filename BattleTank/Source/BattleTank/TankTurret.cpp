// Ben Paolillo - Copyright 2016

#include "BattleTank.h"
#include "TankTurret.h"

void UTankTurret::Rotate(float relativeSpeed)
{
	relativeSpeed = FMath::Clamp(relativeSpeed, -1.0f, 1.0f);

	float rotationChange = relativeSpeed * m_MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float newRotation = RelativeRotation.Yaw + rotationChange;

	SetRelativeRotation(FRotator(0, newRotation, 0));
}


