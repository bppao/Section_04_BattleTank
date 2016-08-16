// Ben Paolillo - Copyright 2016

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

// Forward declarations
class UTankBarrel;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

	public:
		UFUNCTION(BlueprintCallable, Category = "Firing")
		void Fire();

	private:
		// Sets default values for this pawn's properties
		ATank();

		// Called when the game starts or when spawned
		virtual void BeginPlay() override;
	
		UPROPERTY(EditDefaultsOnly, Category = "Setup")
		TSubclassOf<AProjectile> m_ProjectileBlueprint;

		UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float m_ReloadTimeInSeconds = 3.0f;

		// Local barrel reference for spawning projectiles
		UTankBarrel* m_Barrel = nullptr; // TODO Remove this

		float m_LastFireTime = 0.0f;
};
