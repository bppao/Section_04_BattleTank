// Ben Paolillo - Copyright 2016

#include "BattleTank.h"
#include "Tank.h"
#include "TankBarrel.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"
#include "Projectile.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// No need to protect pointers as added at construction
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

void ATank::SetBarrelReference(UTankBarrel* barrelToSet)
{
	TankAimingComponent->SetBarrelReference(barrelToSet);
	m_Barrel = barrelToSet;
}

void ATank::SetTurretReference(UTankTurret* turretToSet)
{
	TankAimingComponent->SetTurretReference(turretToSet);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
}

void ATank::AimAt(FVector hitLocation)
{
	TankAimingComponent->AimAt(hitLocation, m_LaunchSpeed);
}

void ATank::Fire()
{
	bool isReloaded = (GetWorld()->GetTimeSeconds() - m_LastFireTime) > m_ReloadTimeInSeconds;

	// Pointer protection
	if (!m_Barrel) return;

	// Return out if we're not reloaded (i.e., limiting fire rate)
	if (!isReloaded) return;

	// Spawn a projectile at the socket location on the barrel
	AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(
		m_ProjectileBlueprint,
		m_Barrel->GetSocketLocation(FName("Projectile")),
		m_Barrel->GetSocketRotation(FName("Projectile")));

	projectile->LaunchProjectile(m_LaunchSpeed);
	m_LastFireTime = GetWorld()->GetTimeSeconds();
}

