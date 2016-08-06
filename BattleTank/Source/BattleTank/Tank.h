// Ben Paolillo - Copyright 2016

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

// Forward declarations
class UTankBarrel;
class UTankTurret;
class UTankAimingComponent;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

	public:
		UFUNCTION(BlueprintCallable, Category = Setup)
		void SetBarrelReference(UTankBarrel* barrelToSet);

		UFUNCTION(BlueprintCallable, Category = Setup)
		void SetTurretReference(UTankTurret* turretToSet);

		void AimAt(FVector hitLocation);

		UFUNCTION(BlueprintCallable, Category = Firing)
		void Fire();

	protected:
		UTankAimingComponent* TankAimingComponent = nullptr;

	private:
		// Sets default values for this pawn's properties
		ATank();

		// Called when the game starts or when spawned
		virtual void BeginPlay() override;
	
		// Called to bind functionality to input
		virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

		UPROPERTY(EditAnywhere, Category = Firing)
		float m_LaunchSpeed = 4000.0f; // TODO Find sensible default value
};
