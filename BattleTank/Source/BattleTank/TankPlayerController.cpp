// Ben Paolillo - Copyright 2016

#include "BattleTank.h"
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

	FVector hitLocation; // Out parameter
	if (GetSightRayHitLocation(hitLocation))
	{
		//UE_LOG(LogTemp, Warning, TEXT("Look direction: %s"), *hitLocation.ToString());

		// TODO Tell controlled tank to aim at this point
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

	// De-project the screen position of the crosshair to a world direction
	// Line-trace along that look direction and see what we hit (up to max range)
	return true;
}
