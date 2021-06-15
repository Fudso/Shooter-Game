// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/STUPlayerHUDWidget.h"
#include "CustomComponents//SGHealthComponent.h"

int32 USTUPlayerHUDWidget::GetHealthPercent() const
{
	const auto Player = GetOwningPlayerPawn();
	if (!Player)
		return 0;

	const auto Component = Player->GetComponentByClass(USGHealthComponent::StaticClass());
	const auto HealthComponent = Cast<USGHealthComponent>(Component);
	if (!HealthComponent)
		return 0;

	return static_cast<int32>(HealthComponent->GetHealth());
}