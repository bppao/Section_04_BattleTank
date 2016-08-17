// Ben Paolillo - Copyright 2016

#pragma once

#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()
	
	public:	
		// Sets default values for this actor's properties
		AProjectile();

		// Called when the game starts or when spawned
		virtual void BeginPlay() override;

		void LaunchProjectile(float speed);

	private:
		UProjectileMovementComponent* m_ProjectileMovementComponent = nullptr;

		UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* m_CollisionMesh = nullptr;

		UPROPERTY(VisibleAnywhere, Category = "Components")
		UParticleSystemComponent* m_LaunchBlast = nullptr;

		UPROPERTY(VisibleAnywhere, Category = "Components")
		UParticleSystemComponent* m_ImpactBlast = nullptr;

		UFUNCTION()
		void OnHit(UPrimitiveComponent* hitComponent, AActor* otherActor, UPrimitiveComponent* otherComp, FVector normalImpulse, const FHitResult& hit);
};
