// Ben Paolillo - Copyright 2016

#include "BattleTank.h"
#include "TankPlayerController.h"
#include "TankAimingComponent.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UTankAimingComponent* aimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(aimingComponent)) return;

	FoundAimingComponent(aimingComponent);
}

void ATankPlayerController::Tick(float deltaSeconds)
{
	Super::Tick(deltaSeconds);

	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	// If not possessing a tank (e.g., if we died), then return out
	if (!GetPawn()) return;

	UTankAimingComponent* aimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(aimingComponent)) return;

	FVector hitLocation; // OUT parameter
	if (GetSightRayHitLocation(hitLocation))
	{
		aimingComponent->AimAt(hitLocation);
	}
}

// Get world location of linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector &hitLocation) const
{
	// Find the crosshair position
	int32 viewportSizeX, viewportSizeY; // These are OUT parameters
	GetViewportSize(viewportSizeX, viewportSizeY);

	FVector2D screenLocation = FVector2D(
		viewportSizeX * m_CrosshairXLocation,
		viewportSizeY * m_CrosshairYLocation);

	// De-project the screen position of the crosshair to a world direction
	FVector lookDirection;
	if (GetLookDirection(screenLocation, lookDirection))
	{
		// Line-trace along that look direction and see what we hit (up to max range)
		return GetLookVectorHitLocation(lookDirection, hitLocation);
	}

	// Did not get a valid hit location
	return false;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector lookDirection, FVector &hitLocation) const
{
	FHitResult hitResult;
	auto startLocation = PlayerCameraManager->GetCameraLocation();
	auto endLocation = startLocation + (lookDirection * m_LineTraceRange);

	if (GetWorld()->LineTraceSingleByChannel(hitResult, startLocation, endLocation, ECollisionChannel::ECC_Visibility))
	{
		hitLocation = hitResult.Location;
		return true;
	}

	hitLocation = FVector(0);
	return false; // Line-trace didn't hit anything
}

bool ATankPlayerController::GetLookDirection(FVector2D screenLocation, FVector &lookDirection) const
{
	FVector worldLocation; // To be discarded
	return DeprojectScreenPositionToWorld(
		screenLocation.X, screenLocation.Y, worldLocation, lookDirection);
}

