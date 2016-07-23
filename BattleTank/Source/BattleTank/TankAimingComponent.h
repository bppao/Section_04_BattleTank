// Ben Paolillo - Copyright 2016

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

	public:
		// Sets default values for this component's properties
		UTankAimingComponent();

		void SetBarrelReference(UStaticMeshComponent* barrelToSet);

		// TODO Add SetTurretReference

		void AimAt(FVector hitLocation, float launchSpeed);

	private:
		UStaticMeshComponent* m_Barrel = nullptr;

		void MoveBarrelTowards(FVector aimDirection);
};
