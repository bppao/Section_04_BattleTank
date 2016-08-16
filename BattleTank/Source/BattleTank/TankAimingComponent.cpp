// Ben Paolillo - Copyright 2016

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::TickComponent(float deltaTime, enum ELevelTick TickType, FActorComponentTickFunction *thisTickFunction)
{
	if ((GetWorld()->GetTimeSeconds() - m_LastFireTime) > m_ReloadTimeInSeconds)
	{
		m_FiringState = EFiringState::RELOADING;
	}
	// TODO Fix this logic - intentionally stuck in reloading state
}

void UTankAimingComponent::Initialize(UTankBarrel* barrelToSet, UTankTurret* turretToSet)
{
	m_Barrel = barrelToSet;
	m_Turret = turretToSet;
}

void UTankAimingComponent::AimAt(FVector hitLocation)
{
	if (!ensure(m_Barrel)) return;

	FVector launchVelocity; // OUT parameter
	FVector startLocation = m_Barrel->GetSocketLocation(FName("Projectile"));
	TArray<AActor*> actorsToIgnore;

	// Calculate the launchVelocity
	bool haveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		launchVelocity,
		startLocation,
		hitLocation,
		m_LaunchSpeed,
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
	}
}

void UTankAimingComponent::Fire()
{
	// Pointer protection
	if (!ensure(m_Barrel && m_ProjectileBlueprint)) return;

	// Return out if we're not reloaded (i.e., limiting fire rate)
	if (m_FiringState == EFiringState::RELOADING) return;

	// Spawn a projectile at the socket location on the barrel
	AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(
		m_ProjectileBlueprint,
		m_Barrel->GetSocketLocation(FName("Projectile")),
		m_Barrel->GetSocketRotation(FName("Projectile")));

	projectile->LaunchProjectile(m_LaunchSpeed);
	m_LastFireTime = GetWorld()->GetTimeSeconds();
}

void UTankAimingComponent::MoveBarrelTowards(FVector aimDirection)
{
	if (!ensure(m_Barrel && m_Turret)) return;

	// Calculate difference between current barrel rotation and aimDirection
	FRotator barrelRotator = m_Barrel->GetForwardVector().Rotation();
	FRotator aimRotator = aimDirection.Rotation();
	FRotator deltaRotator = aimRotator - barrelRotator;

	m_Barrel->Elevate(deltaRotator.Pitch);
	m_Turret->Rotate(deltaRotator.Yaw);
}
