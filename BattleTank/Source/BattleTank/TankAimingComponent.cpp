// Ben Paolillo - Copyright 2016

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* barrelToSet)
{
	m_Barrel = barrelToSet;
}

void UTankAimingComponent::AimAt(FVector hitLocation, float launchSpeed)
{
	if (!m_Barrel) return;

	FVector launchVelocity; // OUT parameter
	FVector startLocation = m_Barrel->GetSocketLocation(FName("Projectile"));

	// Calculate the launchVelocity
	bool haveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		launchVelocity,
		startLocation,
		hitLocation,
		launchSpeed,
		ESuggestProjVelocityTraceOption::DoNotTrace);

	if (haveAimSolution)
	{
		// Convert the velocity vector into a unit vector
		auto aimDirection = launchVelocity.GetSafeNormal();
		
		MoveBarrelTowards(aimDirection);
	}	
}

void UTankAimingComponent::MoveBarrelTowards(FVector aimDirection)
{
	// Calculate difference between current barrel rotation and aimDirection
	auto barrelRotator = m_Barrel->GetForwardVector().Rotation();
	auto aimRotator = aimDirection.Rotation();
	auto deltaRotator = aimRotator - barrelRotator;

	m_Barrel->Elevate(5);
}
