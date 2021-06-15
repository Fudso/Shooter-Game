// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"

#include "SGHealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeath)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float)

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
	void SetHealth(float fHealth);

	UFUNCTION(BlueprintCallable)
	bool IsDead() const;

public:
	FOnDeath OnDeath;
	FOnHealthChanged OnHealthChanged;
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (ClampMin = "0", ClampMax = "100.0"))
	float MaxHealth = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health")
	bool UseAutoHeal = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health")
	float HealDelay = 3.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health")
	float HealUpdateTime = 0.3f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health")
	float AutoHealValue = 1.0;

	
    UFUNCTION(BlueprintCallable, Category = "Health")
	FString GetHealthPercent() const
	{
		return FString::FromInt(static_cast<int32>(GetHealth()));
	}
	
private:
	float Health = 0.0f;

	FTimerHandle AutoHealDelayTimerHandle;
	FTimerHandle AutoHealUpdateTimerHandle;

private:
	UFUNCTION()
	void OnTakeAnyDamage(
		AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);

	void AutoHeal(float PrevHealth, float CurrentHealth);

	UFUNCTION()
	void OnAutoHealDelayTimeout();

	UFUNCTION()
	void OnAutoHealUpdateTimeout();
};
