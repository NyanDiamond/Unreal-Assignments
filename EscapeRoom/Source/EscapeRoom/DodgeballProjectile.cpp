// Fill out your copyright notice in the Description page of Project Settings.


#include "DodgeballProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "TopDownCharacter.h"

// Sets default values
ADodgeballProjectile::ADodgeballProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	SphereComponent->SetSphereRadius(35.f);
	SphereComponent->SetCollisionProfileName(FName("Dodgeball"));
	SphereComponent->SetSimulatePhysics(true);
	SphereComponent->SetNotifyRigidBodyCollision(true);
	SphereComponent->OnComponentHit.AddDynamic(this, &ADodgeballProjectile::OnHit);
	RootComponent = SphereComponent;
	ProjectileMovement =CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ProjectileMovement->InitialSpeed = 1500.f;

}

void ADodgeballProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (Cast<ATopDownCharacter>(OtherActor) != nullptr)
	{
		//Destroy();
		UGameplayStatics::PlaySoundAtLocation(this, DamageSound, GetActorLocation(), 1.0f, FMath::RandRange(0.7f, 1.3f), 0.0f, BounceSoundAttentuation);

		if (HitParticles != nullptr)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticles, GetActorTransform());
		}
	}

	if (BounceSound != nullptr && NormalImpulse.Size() > 1000.0f)
	{
		UGameplayStatics::PlaySoundAtLocation(this, BounceSound, GetActorLocation(), 1.0f, FMath::RandRange(0.7f, 1.3f), 0.0f, BounceSoundAttentuation);
	}
}


// Called when the game starts or when spawned
void ADodgeballProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	SetLifeSpan(5.f);
}

// Called every frame
void ADodgeballProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

