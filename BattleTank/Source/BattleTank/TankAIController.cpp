// Ben Paolillo - Copyright 2016

#include "BattleTank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	ATank* playerTank = nullptr;
	playerTank = GetPlayerTank();

	if (playerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController found player tank: %s"), *playerTank->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to find player tank"));
	}
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

