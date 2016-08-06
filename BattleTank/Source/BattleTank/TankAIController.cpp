// Ben Paolillo - Copyright 2016

#include "BattleTank.h"
#include "Tank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float deltaSeconds)
{
	Super::Tick(deltaSeconds);

	ATank* playerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	ATank* AIControlledTank = Cast<ATank>(GetPawn());

	if (!playerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to find player tank"));
		return;
	}

	// TODO Move towards the player

	// Aim towards the player
	AIControlledTank->AimAt(playerTank->GetActorLocation());

	AIControlledTank->Fire();
}
