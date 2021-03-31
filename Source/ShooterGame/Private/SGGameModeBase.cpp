// Fill out your copyright notice in the Description page of Project Settings.


#include "SGGameModeBase.h"

#include "Player/SGBaseCharacter.h"
#include "Player/SGPlayerController.h"



ASGGameModeBase::ASGGameModeBase()
{
	DefaultPawnClass = ASGBaseCharacter::StaticClass();
	PlayerControllerClass = ASGPlayerController::StaticClass();
}