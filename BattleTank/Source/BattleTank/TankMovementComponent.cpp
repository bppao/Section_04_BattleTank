// Ben Paolillo - Copyright 2016

#include "BattleTank.h"
#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialize(UTankTrack* leftTrackToSet, UTankTrack* rightTrackToSet)
{
	m_LeftTrack = leftTrackToSet;
	m_RightTrack = rightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float input)
{
	if (!m_LeftTrack || !m_RightTrack) return;

	m_LeftTrack->SetThrottle(input);
	m_RightTrack->SetThrottle(input);
}

void UTankMovementComponent::IntendTurnRight(float input)
{
	if (!m_LeftTrack || !m_RightTrack) return;

	m_LeftTrack->SetThrottle(input);
	m_RightTrack->SetThrottle(-input);
}

void UTankMovementComponent::RequestDirectMove(const FVector& moveVelocity, bool forceMaxSpeed)
{
	// Replacing the functionality of the base class, so don't call Super

	auto name = GetOwner()->GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s moving to: %s"), *name, *moveVelocity.ToString())
}

