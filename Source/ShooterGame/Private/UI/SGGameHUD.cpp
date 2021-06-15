// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SGGameHUD.h"
#include "Engine/Canvas.h"
#include "Blueprint/UserWidget.h"


void ASGGameHUD::BeginPlay()
{
	Super::BeginPlay();
	auto PlayerHUDWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDWidgetClass);
	if (PlayerHUDWidget)
	{
		PlayerHUDWidget->AddToViewport();
	}
}



