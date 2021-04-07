// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"

#include "SGHealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeath)

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SHOOTERGAME_API USGHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USGHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	float GetHealth() const;

	UFUNCTION(BlueprintCallable)
	bool IsDead() const;

public:
	FOnDeath OnDeath;
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (ClampMin = "0", ClampMax = "100.0"))
	float MaxHealth = 100.0f;

private:
	float Health = 0.0f;

private:
	UFUNCTION()
	void OnTakeAnyDamage(
		AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);
};
