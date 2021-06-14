// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animations/STUAnimNotify.h"
#include "STUEquipFinishedAnimNotify.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnNotifiedSignature, USkeletalMeshComponent*);

UCLASS()
class SHOOTERGAME_API USTUEquipFinishedAnimNotify : public USTUAnimNotify
{
	GENERATED_BODY()
	
};
