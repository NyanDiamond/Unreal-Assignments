// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DodgeballProjectile.generated.h"

UCLASS()
class ESCAPEROOM_API ADodgeballProjectile : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Dodgeball, meta = (AllowPrivateAccess = "true"))
		class USphereComponent* SphereComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Dodgeball, meta = (AllowPrivateAccess = "true"))
		class UProjectileMovementComponent* ProjectileMovement;

	
	
public:	
	// Sets default values for this actor's properties
	ADodgeballProjectile();

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = Sound)
		class USoundBase* BounceSound;

	UPROPERTY(EditAnywhere, Category = Sound)
		class USoundBase* DamageSound;

	UPROPERTY(EditAnywhere, Category = Sound)
		class USoundAttenuation* BounceSoundAttentuation;

	UPROPERTY(EditAnywhere, Category = Particles)
		class UParticleSystem* HitParticles;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
