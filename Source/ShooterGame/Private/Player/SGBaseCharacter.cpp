// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SGBaseCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Components/TextRenderComponent.h"

#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/MovementComponent.h"
#include "GameFramework/PawnMovementComponent.h"

#include "CustomComponents/SGCharacterMovementComponent.h"
#include "CustomComponents/SGHealthComponent.h"

// Sets default values
ASGBaseCharacter::ASGBaseCharacter(const FObjectInitializer& ObjInit)
	: Super(ObjInit.SetDefaultSubobjectClass<USGCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);

	HealthComponent = CreateDefaultSubobject<USGHealthComponent>("HealthComponent");

	HealthTextRenderComponent = CreateDefaultSubobject<UTextRenderComponent>("HealthTextRenderComponent");
	HealthTextRenderComponent->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void ASGBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	HealthComponent->OnDeath.AddUObject(this, &ASGBaseCharacter::OnDeath);
}

// Called every frame
void ASGBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const auto Health = HealthComponent->GetHealth();
	HealthTextRenderComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Health)));
}

// Called to bind functionality to input
void ASGBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASGBaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASGBaseCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &ASGBaseCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnAround", this, &ASGBaseCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASGBaseCharacter::Jump);
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ASGBaseCharacter::OnStartRunning);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &ASGBaseCharacter::OnFinishRunning);
	
}

bool ASGBaseCharacter::IsRunning() const
{
	return bWantRunning && bIsMoveForward && !GetVelocity().IsZero();
}

float ASGBaseCharacter::GetCharacterDirection()
{
	const auto Velocity = GetVelocity();

	if (Velocity.IsZero())
	{
		return 0.0f;
	}

	const auto VelocityNormal = Velocity.GetSafeNormal();
	const auto ForwardVector = GetActorForwardVector();
	
	const auto AngleBetween = FMath::Acos(FVector::DotProduct(ForwardVector, VelocityNormal));
	const auto CrossProduct = FVector::CrossProduct(ForwardVector, VelocityNormal);
	const auto Degrees = FMath::RadiansToDegrees(AngleBetween);

	return CrossProduct.IsZero() ? Degrees : Degrees * FMath::Sign(CrossProduct.Z);
	
}

void ASGBaseCharacter::MoveForward(float Amount)
{
	bIsMoveForward = Amount >= 0;
	
	AddMovementInput(GetActorForwardVector(), Amount);
}

void ASGBaseCharacter::MoveRight(float Amount)
{
	AddMovementInput(GetActorRightVector(), Amount);
}

void ASGBaseCharacter::OnStartRunning()
{
	bWantRunning = true;
}

void ASGBaseCharacter::OnFinishRunning()
{
	bWantRunning = false;
}


void ASGBaseCharacter::OnDeath()
{
	PlayAnimMontage(DeathAnimation);

	auto CharacterMovementPtr = GetCharacterMovement();
	CharacterMovementPtr->DisableMovement();

	SetLifeSpan(5.0f);
}



