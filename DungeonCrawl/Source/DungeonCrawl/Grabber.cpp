// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	physicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	// ...
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (physicsHandle == nullptr)
	{
		return;
	}

	FVector TargetLocation = GetComponentLocation() + GetForwardVector() * holdDistance;
	physicsHandle->SetTargetLocationAndRotation(TargetLocation, GetComponentRotation());
	/*FRotator MyRotation = GetComponentRotation();
	FString RotationString = MyRotation.ToCompactString();
	UE_LOG(LogTemp, Display, TEXT("Grabber Rotation: %s"), *RotationString);*/


	
}

	void UGrabber::Grab()
	{

		
		if (physicsHandle == nullptr)
		{
			return;
		}


		FVector Start = GetComponentLocation();
		FVector End = Start + GetForwardVector() * MaxGrabDistance;
		//DrawDebugLine(GetWorld(), Start, End, FColor::Red);

		//Trace Channel: ECC_GameTraceChannel2

		FCollisionShape Sphere = FCollisionShape::MakeSphere(GrabRadius);

		FHitResult HitResult;

		//the gemoetry sweep

		bool HasHit = GetWorld()->SweepSingleByChannel(HitResult, Start, End, FQuat::Identity, ECC_GameTraceChannel2, Sphere);

		if (HasHit)
		{

			UPrimitiveComponent* HitComponent = HitResult.GetComponent();
			HitComponent->WakeAllRigidBodies();
			//DrawDebugSphere(GetWorld(), HitResult.Location, 10, 10, FColor::Green, false, 10);
			//DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10, 10, FColor::Red, false, 10);
			//FString HitActorName = HitResult.GetActor()->GetActorNameOrLabel();
			//UE_LOG(LogTemp, Display, TEXT("Hit actor's name: %s"), *HitActorName);

			physicsHandle->GrabComponentAtLocationWithRotation(HitResult.GetComponent(), NAME_None, HitResult.ImpactPoint, GetComponentRotation());
			FVector TargetLocation = GetComponentLocation() + GetForwardVector() * holdDistance;
			physicsHandle->SetTargetLocationAndRotation(TargetLocation, GetComponentRotation());
		}
		else
		{
			//UE_LOG(LogTemp, Display, TEXT("No actor hit"));
		}
	}

	void UGrabber::Release()
	{
		//UE_LOG(LogTemp, Display, TEXT("Released"));
		
		if (physicsHandle == nullptr)
		{
			return;
		}

		if (physicsHandle->GetGrabbedComponent() != nullptr)
		{
			physicsHandle->GetGrabbedComponent()->WakeAllRigidBodies();
			physicsHandle->ReleaseComponent();
		}
	}

