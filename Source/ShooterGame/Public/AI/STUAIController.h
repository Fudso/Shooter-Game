// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "STUAIController.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERGAME_API ASTUAIController : public AAIController
{
	GENERATED_BODY()

	protected:
	virtual void OnPossess(APawn* InPawn) override;
	
};
