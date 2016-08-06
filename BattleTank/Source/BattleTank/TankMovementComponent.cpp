// Ben Paolillo - Copyright 2016

#include "BattleTank.h"
#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialize(UTankTrack* leftTrackToSet, UTankTrack* rightTrackToSet)
{
	if (!leftTrackToSet || !rightTrackToSet) return;

	m_LeftTrack = leftTrackToSet;
	m_RightTrack = rightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float input)
{
	UE_LOG(LogTemp, Warning, TEXT("Intend move forward input: %f"), input);

	m_LeftTrack->SetThrottle(input);
	m_RightTrack->SetThrottle(input);
}

