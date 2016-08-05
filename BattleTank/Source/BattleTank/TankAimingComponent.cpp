// Ben Paolillo - Copyright 2016

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
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

void UTankAimingComponent::SetTurretReference(UTankTurret* turretToSet)
{
	m_Turret = turretToSet;
}

void UTankAimingComponent::AimAt(FVector hitLocation, float launchSpeed)
{
	if (!m_Barrel) return;

	FVector launchVelocity; // OUT parameter
	FVector startLocation = m_Barrel->GetSocketLocation(FName("Projectile"));
	TArray<AActor*> actorsToIgnore;

	// Calculate the launchVelocity
	bool haveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		launchVelocity,
		startLocation,
		hitLocation,
		launchSpeed,
		false,
		0.0f,
		0.0f,
		ESuggestProjVelocityTraceOption::DoNotTrace,
		FCollisionResponseParams::DefaultResponseParam,
		actorsToIgnore,
		false);

	if (haveAimSolution)
	{
		// Convert the velocity vector into a unit vector
		auto aimDirection = launchVelocity.GetSafeNormal();
		MoveBarrelTowards(aimDirection);

		auto time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f: Aim solution found"), time);
	}
	else
	{
		auto time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f: No aim solution found"), time);
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector aimDirection)
{
	// Calculate difference between current barrel rotation and aimDirection
	FRotator barrelRotator = m_Barrel->GetForwardVector().Rotation();
	FRotator aimRotator = aimDirection.Rotation();
	FRotator deltaRotator = aimRotator - barrelRotator;

	m_Barrel->Elevate(deltaRotator.Pitch);
	m_Turret->Rotate(deltaRotator.Yaw);
}
