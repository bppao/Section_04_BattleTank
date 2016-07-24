// Ben Paolillo - Copyright 2016

#include "BattleTank.h"
#include "Tank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	m_PlayerTank = GetPlayerTank();

	if (m_PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController found player tank: %s"), *m_PlayerTank->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to find player tank"));
	}
}

void ATankAIController::Tick(float deltaSeconds)
{
	Super::Tick(deltaSeconds);

	if (!m_PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to find player tank"));
	}

	// TODO Move towards the player

	// Aim towards the player
	GetControlledTank()->AimAt(m_PlayerTank->GetActorLocation());

	// TODO Fire if ready
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	APawn* playerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	return Cast<ATank>(playerTank);
}

