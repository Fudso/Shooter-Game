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

	Health = MaxHealth;

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
	if (Damage <= 0.0f && IsDead())
	{
		return;
	}
	
	Health = FMath::Clamp(Health - Damage, 0.0f, MaxHealth);

	if (IsDead())
	{
		OnDeath.Broadcast();
	}
}