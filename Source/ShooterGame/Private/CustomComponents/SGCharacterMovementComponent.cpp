// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomComponents/SGCharacterMovementComponent.h"
#include "Player/SGBaseCharacter.h"

float USGCharacterMovementComponent::GetMaxSpeed() const
{
	const float MaxSpeed = Super::GetMaxSpeed();
	const auto Player = Cast <ASGBaseCharacter>(GetPawnOwner());

	return Player && Player->IsRunning() ? MaxSpeed * RunModifier : MaxSpeed;
}