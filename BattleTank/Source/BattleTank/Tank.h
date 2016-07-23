// Ben Paolillo - Copyright 2016

#pragma once

#include "TankAimingComponent.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel; // Forward declaration

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

	public:
		void AimAt(FVector hitLocation);

		UFUNCTION(BlueprintCallable, Category = Setup)
		void SetBarrelReference(UTankBarrel* barrelToSet);

	protected:
		UTankAimingComponent* TankAimingComponent = nullptr;

	private:
		// Sets default values for this pawn's properties
		ATank();

		// Called when the game starts or when spawned
		virtual void BeginPlay() override;
	
		// Called every frame
		virtual void Tick( float DeltaSeconds ) override;

		// Called to bind functionality to input
		virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

		UPROPERTY(EditAnywhere, Category = Firing)
		float m_LaunchSpeed = 100000.0f; // TODO Find sensible default value
};
