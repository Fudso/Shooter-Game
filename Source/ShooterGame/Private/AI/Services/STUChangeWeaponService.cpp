// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Services/STUChangeWeaponService.h"
#include "CustomComponents/SGWeaponComponent.h"
#include "AIController.h"
#include "STUUtils.h"

USTUChangeWeaponService::USTUChangeWeaponService()
{
	NodeName = "Change Weapon";
}

void USTUChangeWeaponService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Controller = OwnerComp.GetAIOwner();
	if (Controller)
	{
		const auto WeaponComponent = STUUtils::GetSTUPlayerComponent<USGWeaponComponent>(Controller->GetPawn());
		if (WeaponComponent && Probability > 0 && FMath::FRand() <= Probability)
		{
			WeaponComponent->NextWeapon();
		}
	}

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
