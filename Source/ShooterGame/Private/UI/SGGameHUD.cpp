// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SGGameHUD.h"
#include "Engine/Canvas.h"

void ASGGameHUD::DrawHUD()
{
	Super::DrawHUD();

	DrawCrossHair();
}

void ASGGameHUD::DrawCrossHair()
{
	const int32 CenterX = Canvas->SizeX;
	const int32 CenterY = Canvas->SizeY;

	const TInterval<float> Center(CenterX * 0.5f, CenterY * 0.5);

	const float HalfLineSize = 10.0f;
	const float LineThickness = 2.0f;
	const FLinearColor LinearColor = FLinearColor::Green;

	
	DrawLine(
		Center.Min - HalfLineSize, Center.Max,
		Center.Min + HalfLineSize, Center.Max, 
		LinearColor, LineThickness);

	DrawLine(Center.Min, Center.Max - HalfLineSize,
		Center.Min, Center.Max + HalfLineSize, 
		LinearColor, LineThickness);
}
