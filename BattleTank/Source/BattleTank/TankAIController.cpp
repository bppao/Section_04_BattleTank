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

	// Move towards the player
	MoveToActor(playerTank, m_AcceptanceRadius); // TODO Check radius is in cm

	// Aim towards the player
	AIControlledTank->AimAt(playerTank->GetActorLocation());

	AIControlledTank->Fire();
}
