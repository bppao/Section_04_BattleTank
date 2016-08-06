// Ben Paolillo - Copyright 2016

#include "BattleTank.h"
#include "TankTrack.h"

void UTankTrack::SetThrottle(float throttle)
{
	auto name = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s throttle: %f!"), *name, throttle);

	// TODO Clamp throttle value so the user can't increase the scale and make the tank move faster
	FVector forceApplied = GetForwardVector() * throttle * TrackMaxDrivingForce;
	FVector forceLocation = GetComponentLocation();

	// Get the root tank component and add force at the location of the track
	UPrimitiveComponent* tankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	tankRoot->AddForceAtLocation(forceApplied, forceLocation);
}

