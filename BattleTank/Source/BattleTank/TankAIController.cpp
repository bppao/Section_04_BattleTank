// Ben Paolillo - Copyright 2016

#include "BattleTank.h"
#include "TankAIController.h"
#include "TankAimingComponent.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float deltaSeconds)
{
	Super::Tick(deltaSeconds);

	APawn* playerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	APawn* AIControlledTank = GetPawn();

	if (!ensure(playerTank && AIControlledTank)) return;

	// Move towards the player
	MoveToActor(playerTank, m_AcceptanceRadius); // TODO Check radius is in cm

	// Aim towards the player
	UTankAimingComponent* AIAimingComponent = AIControlledTank->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AIAimingComponent)) return;
	AIAimingComponent->AimAt(playerTank->GetActorLocation());

	// Only allow the AI tanks to fire if they're locked on the player
	if (AIAimingComponent->GetFiringState() == EFiringState::LOCKED)
	{
		AIAimingComponent->Fire(); // TODO Limit firing rate
	}
}
