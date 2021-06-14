// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SGGameHUD.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERGAME_API ASGGameHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void DrawHUD() override;

private:
	void DrawCrossHair();
	
};
