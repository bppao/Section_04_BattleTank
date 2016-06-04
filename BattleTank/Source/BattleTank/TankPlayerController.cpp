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
	if (!GetControlledTank()) return;

	// Get world location if linetrace through crosshair
	// If it hits the landscape
		// Tell controlled tank to aim at this point
}
