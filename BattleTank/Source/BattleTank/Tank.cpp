// Ben Paolillo - Copyright 2016

#include "BattleTank.h"
#include "Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
}

float ATank::TakeDamage(float damageAmount, struct FDamageEvent const &DamageEvent, class AController *eventInstigator, AActor *damageCauser)
{
	// Convert the float into an int because we only want to compare integers here
	int32 damagePoints = FPlatformMath::RoundToInt(damageAmount);

	// Clamp it to the actor's current health so we always end up at 0 health precisely
	int32 damageToApply = FMath::Clamp(damagePoints, 0, m_CurrentHealth);
	
	m_CurrentHealth -= damageToApply;

	if (m_CurrentHealth <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank died!"))
	}

	return damageToApply;
}

