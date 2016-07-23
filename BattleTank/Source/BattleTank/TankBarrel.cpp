// Ben Paolillo - Copyright 2016

#include "BattleTank.h"
#include "TankBarrel.h"

void UTankBarrel::Elevate(float degreesPerSecond)
{
	// Move the barrel the right amount this frame given a max elevation speed
	// and frame time
	UE_LOG(LogTemp, Warning, TEXT("m_Barrel->Elevate() called at speed %f"), degreesPerSecond);
}


