// Ben Paolillo - Copyright 2016

#include "BattleTank.h"
#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::BeginPlay()
{
	// Subscribe to this hit event
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::TickComponent(float deltaTime, enum ELevelTick TickType, FActorComponentTickFunction *thisTickFunction)
{
	// Calculate the slippage speed (sideways-component of the vector)
	float slippageSpeed = FVector::DotProduct(GetComponentVelocity(), GetRightVector());

	// Calculate the required acceleration this frame to correct
	FVector correctionAcceleration = (-slippageSpeed / deltaTime) * GetRightVector();

	// Calculate and apply sideways force (F = m * a)
	UStaticMeshComponent* tankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	FVector correctionForce = (tankRoot->GetMass() * correctionAcceleration) / 2; // Two tracks
	tankRoot->AddForce(correctionForce);
}

void UTankTrack::OnHit(UPrimitiveComponent* hitComponent, AActor* otherActor, UPrimitiveComponent* otherComp, FVector normalImpulse, const FHitResult& hit)
{
	UE_LOG(LogTemp, Warning, TEXT("Track is on the ground!"))
}

void UTankTrack::SetThrottle(float throttle)
{
	FVector forceApplied = GetForwardVector() * throttle * TrackMaxDrivingForce;
	FVector forceLocation = GetComponentLocation();

	// Get the root tank component and add force at the location of the track
	UPrimitiveComponent* tankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	tankRoot->AddForceAtLocation(forceApplied, forceLocation);
}


