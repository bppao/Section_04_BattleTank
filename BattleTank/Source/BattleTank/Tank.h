// Ben Paolillo - Copyright 2016

#pragma once

#include "TankAimingComponent.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

	public:
		void AimAt(FVector hitLocation);

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
};
