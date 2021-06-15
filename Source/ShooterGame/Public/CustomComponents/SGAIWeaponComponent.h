// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CustomComponents/SGWeaponComponent.h"
#include "SGAIWeaponComponent.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERGAME_API USGAIWeaponComponent : public USGWeaponComponent
{
	GENERATED_BODY()

	public:
	virtual void StartFire() override;
	virtual void NextWeapon() override;
	
};
