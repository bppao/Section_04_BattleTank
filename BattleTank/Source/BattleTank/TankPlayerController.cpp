// Ben Paolillo - Copyright 2016

#include "BattleTank.h"
#include "Tank.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ATank* controlledTank = nullptr;
	controlledTank = GetControlledTank();

	if (controlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Controlled Tank: %s"), *controlledTank->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to possess tank"));
	}
}

void ATankPlayerController::Tick(float deltaSeconds)
{
	Super::Tick(deltaSeconds);

	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	// Doesn't make sense to aim towards the crosshair
	// if the player is not controlling a tank
	if (!GetControlledTank()) return;

	FVector hitLocation; // OUT parameter
	if (GetSightRayHitLocation(hitLocation))
	{
		GetControlledTank()->AimAt(hitLocation);
	}
}

// Get world location of linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector &hitLocation) const
{
	// Find the crosshair position
	int32 viewportSizeX, viewportSizeY; // These are OUT parameters
	GetViewportSize(viewportSizeX, viewportSizeY);

	FVector2D screenLocation =
		FVector2D(viewportSizeX * m_CrosshairXLocation,
				  viewportSizeY * m_CrosshairYLocation);
	FVector lookDirection;

	// De-project the screen position of the crosshair to a world direction
	if (GetLookDirection(screenLocation, lookDirection))
	{
		// Line-trace along that look direction and see what we hit (up to max range)
		GetLookVectorHitLocation(lookDirection, hitLocation);
	}

	return true;
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

