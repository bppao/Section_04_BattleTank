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
	LOCKED,
	OUT_OF_AMMO
};

// Forward declaration
class UTankBarrel;
class UTankTurret;
class AProjectile;

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

		void AimAt(FVector hitLocation);

		UFUNCTION(BlueprintCallable, Category = "Firing")
		void Fire();

		EFiringState GetFiringState() const;

		UFUNCTION(BlueprintCallable, Category = "Firing")
		int32 GetRoundsLeft() const;

	protected:
		UPROPERTY(BlueprintReadOnly, Category = "State")
		EFiringState FiringState = EFiringState::RELOADING;

	private:
		UTankBarrel* m_Barrel = nullptr;
		UTankTurret* m_Turret = nullptr;

		UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float m_LaunchSpeed = 4000.0f;

		UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float m_ReloadTimeInSeconds = 3.0f;

		// Ammo to start with
		UPROPERTY(EditDefaultsOnly, Category = "Firing")
		int32 m_RoundsLeft = 3;

		// Sound that plays when the player or AI tank fires
		UPROPERTY(EditDefaultsOnly, Category = "Firing")
		USoundBase* m_FireSound = nullptr;

		UPROPERTY(EditDefaultsOnly, Category = "Setup")
		TSubclassOf<AProjectile> m_ProjectileBlueprint;

		float m_LastFireTime = 0.0f;

		FVector m_AimDirection;

		virtual void TickComponent(float deltaTime, enum ELevelTick TickType, FActorComponentTickFunction *thisTickFunction) override;

		void MoveBarrelTowards(FVector aimDirection);

		bool IsBarrelMoving();
};
