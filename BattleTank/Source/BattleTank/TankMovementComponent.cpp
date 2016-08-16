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
	if (!ensure(m_LeftTrack && m_RightTrack)) return;

	m_LeftTrack->SetThrottle(input);
	m_RightTrack->SetThrottle(input);
}

void UTankMovementComponent::IntendTurnRight(float input)
{
	if (!ensure(m_LeftTrack && m_RightTrack)) return;

	m_LeftTrack->SetThrottle(input);
	m_RightTrack->SetThrottle(-input);
}

void UTankMovementComponent::RequestDirectMove(const FVector& moveVelocity, bool forceMaxSpeed)
{
	// Replacing the functionality of the base class, so don't call Super

	// Only care about the direction that the AI tank wants to move in,
	// so normalize the velocity vector
	FVector AIMoveDirection = moveVelocity.GetSafeNormal();
	FVector tankForwardDirection = GetOwner()->GetActorForwardVector().GetSafeNormal();

	// Calculate the dot product between the two vectors to drive the AI tank
	// in the correct forward/backward direction
	float AIDriveInputForwardBackward = FVector::DotProduct(AIMoveDirection, tankForwardDirection);
	IntendMoveForward(AIDriveInputForwardBackward);

	// Calculate the cross product between the two vectors to drive the AI tank
	// in the correct right/left direction
	FVector AIDriveInputRightLeft = FVector::CrossProduct(tankForwardDirection, AIMoveDirection);
	IntendTurnRight(AIDriveInputRightLeft.Z);
}

