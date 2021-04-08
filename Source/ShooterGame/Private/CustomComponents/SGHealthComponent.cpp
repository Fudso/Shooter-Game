// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomComponents/SGHealthComponent.h"

#include "GameFramework/Actor.h"


// Sets default values for this component's properties
USGHealthComponent::USGHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void USGHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

	SetHealth(MaxHealth);

	auto OwnerActor = GetOwner();

	if (OwnerActor)
	{
		OwnerActor->OnTakeAnyDamage.AddDynamic(this, &USGHealthComponent::OnTakeAnyDamage);
	}
	
}

float USGHealthComponent::GetHealth() const
{
	return Health;
}

void USGHealthComponent::SetHealth(float fHealth)
{
	fHealth = FMath::Clamp(fHealth, 0.0f, MaxHealth);
	
	if (FMath::IsNearlyEqual(Health, fHealth))
	{
		return;
	}

	AutoHeal(Health, fHealth);
	
	Health = fHealth;
	
	OnHealthChanged.Broadcast(Health);
}

bool USGHealthComponent::IsDead() const
{
	return Health <= 0.0f;
}

void USGHealthComponent::OnTakeAnyDamage(
	AActor* DamagedActor, 
	float Damage,
	const UDamageType* DamageType, 
	AController* InstigatedBy, 
	AActor* DamageCauser)
{
	if (Damage <= 0.0f || IsDead())
	{
		return;
	}

	const float CurrentHealth = Health - Damage;
	
	SetHealth(CurrentHealth);

	if (IsDead())
	{
		OnDeath.Broadcast();
	}
}

void USGHealthComponent::AutoHeal(float PrevHealth, float CurrentHealth)
{
	auto World = GetWorld();
	
	if (!UseAutoHeal || !World || CurrentHealth >= PrevHealth)
	{
		return;;
	}

	auto& TimerManager = World->GetTimerManager();

	TimerManager.ClearTimer(AutoHealDelayTimerHandle);
	TimerManager.ClearTimer(AutoHealUpdateTimerHandle);

	if (CurrentHealth <= 0 || CurrentHealth >= MaxHealth)
	{
		return;
	}

	if (CurrentHealth < PrevHealth)
	{
		TimerManager.SetTimer(
			AutoHealDelayTimerHandle,
			this,
			&USGHealthComponent::OnAutoHealDelayTimeout, 
			HealDelay
		);
	}
}


void USGHealthComponent::OnAutoHealDelayTimeout()
{
	auto World = GetWorld();

	if (!World)
	{
		return;;
	}
	
	auto& TimerManager = World->GetTimerManager();
	
	TimerManager.SetTimer(
		AutoHealUpdateTimerHandle,
		this,
		&USGHealthComponent::OnAutoHealUpdateTimeout,
		HealUpdateTime,
		true
	);
}


void USGHealthComponent::OnAutoHealUpdateTimeout()
{
	const float CurrentHealth = Health + AutoHealValue;

	SetHealth(CurrentHealth);
}