// Ben Paolillo - Copyright 2016

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Enum for aiming state
UENUM()
enum class EFiringState : uint8
{
	RELOADING,
	AIMING,
	LOCKED
};

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

		UFUNCTION(BlueprintCallable, Category = "Setup")
		void Initialize(UTankBarrel* barrelToSet, UTankTurret* turretToSet);

		void AimAt(FVector hitLocation, float launchSpeed);

	protected:
		UPROPERTY(BlueprintReadOnly, Category = "State")
		EFiringState m_FiringState = EFiringState::RELOADING;

	private:
		UTankBarrel* m_Barrel = nullptr;
		UTankTurret* m_Turret = nullptr;

		void MoveBarrelTowards(FVector aimDirection);
};
