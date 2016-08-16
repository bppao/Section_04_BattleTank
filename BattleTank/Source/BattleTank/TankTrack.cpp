// Ben Paolillo - Copyright 2016

#include "BattleTank.h"
#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay()
{
	// Subscribe to this hit event
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::ApplySidewaysForce()
{
	// Calculate the slippage speed (sideways-component of the vector)
	float slippageSpeed = FVector::DotProduct(GetComponentVelocity(), GetRightVector());

	// Calculate the required acceleration this frame to correct
	float deltaTime = GetWorld()->GetDeltaSeconds();
	FVector correctionAcceleration = (-slippageSpeed / deltaTime) * GetRightVector();

	// Calculate and apply sideways force (F = m * a)
	UStaticMeshComponent* tankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	FVector correctionForce = (tankRoot->GetMass() * correctionAcceleration) / 2; // Two tracks
	tankRoot->AddForce(correctionForce);
}

void UTankTrack::OnHit(UPrimitiveComponent* hitComponent, AActor* otherActor, UPrimitiveComponent* otherComp, FVector normalImpulse, const FHitResult& hit)
{
	DriveTrack();
	ApplySidewaysForce();

	UStaticMeshComponent* tankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());

	// Set no linear or angular damping if we are trying to drive the tank
	if (m_CurrentThrottle > 0.0f)
	{
		tankRoot->SetLinearDamping(0.0f);
		tankRoot->SetAngularDamping(0.0f);
	}

	// Reset the current throttle so the tank doesn't keep driving forward on its own
	m_CurrentThrottle = 0.0f;
	tankRoot->SetLinearDamping(0.5f);
	tankRoot->SetAngularDamping(0.8f);
}

void UTankTrack::SetThrottle(float throttle)
{
	m_CurrentThrottle = FMath::Clamp(m_CurrentThrottle + throttle, -1.0f, 1.0f);
}

void UTankTrack::DriveTrack()
{
	FVector forceApplied = GetForwardVector() * m_CurrentThrottle * TrackMaxDrivingForce;
	FVector forceLocation = GetComponentLocation();

	// Get the root tank component and add force at the location of the track
	UPrimitiveComponent* tankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	tankRoot->AddForceAtLocation(forceApplied, forceLocation);
}


