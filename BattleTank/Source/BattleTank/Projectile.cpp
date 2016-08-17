// Ben Paolillo - Copyright 2016

#include "BattleTank.h"
#include "Projectile.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
	SetRootComponent(m_CollisionMesh);
	m_CollisionMesh->SetNotifyRigidBodyCollision(true);
	m_CollisionMesh->SetVisibility(false);

	m_LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast"));
	m_LaunchBlast->AttachTo(RootComponent);

	m_ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Movement Component"));
	m_ProjectileMovementComponent->bAutoActivate = false;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();	
}

// Called every frame
void AProjectile::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

void AProjectile::LaunchProjectile(float speed)
{
	m_ProjectileMovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector * speed);
	m_ProjectileMovementComponent->Activate();
}

