// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUCoreTypes.h"
#include "STUPlayerHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERGAME_API USTUPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	int32 GetHealthPercent() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	bool GetWeaponUIData(FWeaponUIData& UIData) const;
};
