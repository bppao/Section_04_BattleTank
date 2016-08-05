// Ben Paolillo - Copyright 2016

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Forward declaration
class UTankBarrel;
class UTankTurret;

// Holds barrel's properties and Elevate method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

	public:
		// Sets default values for this component's properties
		UTankAimingComponent();

		void SetBarrelReference(UTankBarrel* barrelToSet);

		void SetTurretReference(UTankTurret* turretToSet);

		void AimAt(FVector hitLocation, float launchSpeed);

	private:
		UTankBarrel* m_Barrel = nullptr;

		UTankTurret* m_Turret = nullptr;

		void MoveBarrelTowards(FVector aimDirection);
};
