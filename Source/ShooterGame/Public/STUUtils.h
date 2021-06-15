// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class STUUtils
{
public:
	template <typename T>
	static T* GetSTUPlayerComponent(AActor* PlayerPawn)
	{
		if (!PlayerPawn)
			return nullptr;

		const auto Component = PlayerPawn->GetComponentByClass(T::StaticClass());
		return Cast<T>(Component);
	}
};