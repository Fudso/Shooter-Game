// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SGBaseCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"


// Sets default values
ASGBaseCharacter::ASGBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);
	
}

// Called when the game starts or when spawned
void ASGBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASGBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASGBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASGBaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASGBaseCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &ASGBaseCharacter::LookUp);
	PlayerInputComponent->BindAxis("TurnAround", this, &ASGBaseCharacter::TurnAround);
	
}

void ASGBaseCharacter::MoveForward(float Amount)
{
	AddMovementInput(GetActorForwardVector(), Amount);
}

void ASGBaseCharacter::MoveRight(float Amount)
{
	AddMovementInput(GetActorRightVector(), Amount);
}

void ASGBaseCharacter::LookUp(float Amount)
{
	AddControllerPitchInput(Amount);
}

void ASGBaseCharacter::TurnAround(float Amount)
{
	AddControllerYawInput(Amount);
}