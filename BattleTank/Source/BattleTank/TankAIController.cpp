// Ben Paolillo - Copyright 2016

#include "BattleTank.h"
#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float deltaSeconds)
{
	Super::Tick(deltaSeconds);

	APawn* playerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	APawn* AIControlledTank = GetPawn();

	if (!(playerTank && AIControlledTank)) return;

	// Move towards the player
	MoveToActor(playerTank, AcceptanceRadius);

	// Aim towards the player
	UTankAimingComponent* AIAimingComponent = AIControlledTank->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AIAimingComponent)) return;
	AIAimingComponent->AimAt(playerTank->GetActorLocation());

	// Only allow the AI tanks to fire if they're locked on the player
	if (AIAimingComponent->GetFiringState() == EFiringState::LOCKED)
	{
		AIAimingComponent->Fire();
	}
}

void ATankAIController::SetPawn(APawn* inPawn)
{
	Super::SetPawn(inPawn);

	// Don't continue if we're not possessing a pawn
	if (!inPawn) return;

	ATank* possessedTank = Cast<ATank>(inPawn);
	if (!ensure(possessedTank)) return;

	// Subscribe to the tank's death event
	possessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnTankDeath);
}

void ATankAIController::OnTankDeath()
{
	if (!GetPawn()) return;

	// Stop the AI tank from firing at the player if the AI tank is dead
	GetPawn()->DetachFromControllerPendingDestroy();
}
