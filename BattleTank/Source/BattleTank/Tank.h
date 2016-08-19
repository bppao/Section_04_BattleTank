// Ben Paolillo - Copyright 2016

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDeathDelegate);

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

	public:
		// Return current health as a percentage of starting health between 0 and 1
		UFUNCTION(BlueprintPure, Category = "Health")
		float GetHealthPercent() const;
		
		// Called by the engine when actor damage is dealt
		virtual float TakeDamage(float damageAmount, struct FDamageEvent const &DamageEvent, class AController *eventInstigator, AActor *damageCauser) override;

		void ActivateOnDeathBlast();

		FTankDeathDelegate OnDeath;

	private:
		// Sets default values for this pawn's properties
		ATank();

		// Called when the game starts or when spawned
		virtual void BeginPlay() override;

		UPROPERTY(EditDefaultsOnly, Category = "Setup")
		int32 m_StartingHealth = 100;

		UPROPERTY(VisibleAnywhere, Category = "Setup")
		int32 m_CurrentHealth;
};
