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

void UTankAimingComponent::Initialize(UTankBarrel* barrelToSet, UTankTurret* turretToSet)
{
	m_Barrel = barrelToSet;
	m_Turret = turretToSet;
}

void UTankAimingComponent::TickComponent(float deltaTime, enum ELevelTick TickType, FActorComponentTickFunction *thisTickFunction)
{
	if (m_RoundsLeft <= 0 || GetWorld()->GetFirstPlayerController()->PlayerState->bIsSpectator)
	{
		FiringState = EFiringState::OUT_OF_AMMO;
	}
	else if ((GetWorld()->GetTimeSeconds() - m_LastFireTime) < m_ReloadTimeInSeconds)
	{
		FiringState = EFiringState::RELOADING;
	}
	else if (IsBarrelMoving())
	{
		FiringState = EFiringState::AIMING;
	}
	else
	{
		FiringState = EFiringState::LOCKED;
	}
}

EFiringState UTankAimingComponent::GetFiringState() const
{
	return FiringState;
}

int32 UTankAimingComponent::GetRoundsLeft() const
{
	return m_RoundsLeft;
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
		m_AimDirection = launchVelocity.GetSafeNormal();
		MoveBarrelTowards(m_AimDirection);
	}
}

void UTankAimingComponent::Fire()
{
	// Pointer protection
	if (!ensure(m_Barrel && m_ProjectileBlueprint)) return;

	// Return out if we're reloading or if we're out of ammo
	if (FiringState == EFiringState::RELOADING ||
		FiringState == EFiringState::OUT_OF_AMMO) return;

	// Spawn a projectile at the socket location on the barrel
	AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(
		m_ProjectileBlueprint,
		m_Barrel->GetSocketLocation(FName("Projectile")),
		m_Barrel->GetSocketRotation(FName("Projectile")));

	projectile->LaunchProjectile(m_LaunchSpeed);
	m_LastFireTime = GetWorld()->GetTimeSeconds();

	m_RoundsLeft--;
}

void UTankAimingComponent::MoveBarrelTowards(FVector aimDirection)
{
	if (!ensure(m_Barrel && m_Turret)) return;

	// Calculate difference between current barrel rotation and aimDirection
	FRotator barrelRotator = m_Barrel->GetForwardVector().Rotation();
	FRotator aimRotator = aimDirection.Rotation();
	FRotator deltaRotator = aimRotator - barrelRotator;

	m_Barrel->Elevate(deltaRotator.Pitch);

	// If we need to rotate more than 180 degrees, then go the other way.
	// This will ensure that the turret always takes the shortest route
	// to line up the barrel with the mouse cursor.
	if (FMath::Abs(deltaRotator.Yaw) > 180.0f)
	{
		m_Turret->Rotate(-deltaRotator.Yaw);
	}
	else
	{
		m_Turret->Rotate(deltaRotator.Yaw);
	}
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(m_Barrel)) return false;

	return !m_Barrel->GetForwardVector().Equals(m_AimDirection, 0.025f);
}
