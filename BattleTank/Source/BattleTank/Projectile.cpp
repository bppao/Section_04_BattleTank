// Ben Paolillo - Copyright 2016

#include "BattleTank.h"
#include "Projectile.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	m_CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
	SetRootComponent(m_CollisionMesh);
	m_CollisionMesh->SetNotifyRigidBodyCollision(true);
	m_CollisionMesh->SetVisibility(false);

	m_LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast"));
	m_LaunchBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	m_ImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Impact Blast"));
	m_ImpactBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	m_ImpactBlast->bAutoActivate = false;

	m_ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Movement Component"));
	m_ProjectileMovementComponent->bAutoActivate = false;

	m_ExplosionForce = CreateDefaultSubobject<URadialForceComponent>(FName("Explosion Force"));
	m_ExplosionForce->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	// Subscribe to this hit event
	m_CollisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

void AProjectile::LaunchProjectile(float speed)
{
	m_ProjectileMovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector * speed);
	m_ProjectileMovementComponent->Activate();
}

void AProjectile::OnHit(UPrimitiveComponent* hitComponent, AActor* otherActor, UPrimitiveComponent* otherComp, FVector normalImpulse, const FHitResult& hit)
{
	m_LaunchBlast->Deactivate();
	m_ImpactBlast->Activate();
	m_ExplosionForce->FireImpulse();

	// Destroy the collision mesh component once it has hit something
	SetRootComponent(m_ImpactBlast);
	m_CollisionMesh->DestroyComponent();

	// Setup a timer to destroy the projectile altogether once the timer has expired
	FTimerHandle destroyTimer;
	GetWorld()->GetTimerManager().SetTimer(destroyTimer, this, &AProjectile::OnDestroyTimerExpire, m_DestroyDelay, false);
}

void AProjectile::OnDestroyTimerExpire()
{
	Destroy();
}

