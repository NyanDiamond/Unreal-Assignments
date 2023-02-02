// Fill out your copyright notice in the Description page of Project Settings.


#include "MyFirstPersonCharacter.h"

// Sets default values
AMyFirstPersonCharacter::AMyFirstPersonCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyFirstPersonCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyFirstPersonCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyFirstPersonCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//Setup input bindings

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AMyFirstPersonCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AMyFirstPersonCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AMyFirstPersonCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AMyFirstPersonCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed,this, &AMyFirstPersonCharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Released,this, &AMyFirstPersonCharacter::Jump);

}

void AMyFirstPersonCharacter::MoveForward(float Axisval)
{
	AddMovementInput(GetActorForwardVector() * Axisval);
}

void AMyFirstPersonCharacter::MoveRight(float Axisval)
{
	AddMovementInput(GetActorRightVector() * Axisval);
}



