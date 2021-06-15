// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/SGBaseCharacter.h"
#include "STUAICharacter.generated.h"


class UBehaviorTree;

UCLASS()
class SHOOTERGAME_API ASTUAICharacter : public ASGBaseCharacter
{
	GENERATED_BODY()

	
public:
	ASTUAICharacter(const FObjectInitializer& ObjInit);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
	UBehaviorTree* BehaviorTreeAsset;

	protected:
	virtual void OnDeath() override;
};
