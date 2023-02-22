// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveActorComponent.h"

// Sets default values for this component's properties
UMoveActorComponent::UMoveActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMoveActorComponent::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetOwner()->GetActorLocation();

	// ...

	FString ActorName = GetOwner()->GetActorNameOrLabel();

	FString PositionOfObject = GetOwner()->GetActorLocation().ToString();

	UE_LOG(LogTemp, Warning, TEXT("Actor %s is at location %s"), *ActorName, *PositionOfObject);

	UE_LOG(LogTemp, Warning, TEXT("Actor %s is at x: %f, y: %f"), *ActorName, GetOwner()->GetActorLocation().X, GetOwner()->GetActorLocation().Y);
	
}


// Called every frame
void UMoveActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	MoveActor(DeltaTime);
	RotateActor(DeltaTime);
}

void UMoveActorComponent::MoveActor(float DeltaTime)
{
	FVector CurrentLocation = GetOwner()->GetActorLocation();

	CurrentLocation = CurrentLocation + MoveVelocity * DeltaTime;

	GetOwner()->SetActorLocation(CurrentLocation);

	float DistanceMoved = FVector::Dist(StartLocation, CurrentLocation);

	if (DistanceMoved >= MoveDistance)
	{
		FVector MoveDirection = MoveVelocity.GetSafeNormal();

		StartLocation = StartLocation + MoveDirection * MoveDistance;

		GetOwner()->SetActorLocation(StartLocation);

		MoveVelocity = -MoveVelocity;
	}
}

void UMoveActorComponent::RotateActor(float DeltaTime)
{
	GetOwner()->AddActorLocalRotation(RotationVelocity * DeltaTime);
}





