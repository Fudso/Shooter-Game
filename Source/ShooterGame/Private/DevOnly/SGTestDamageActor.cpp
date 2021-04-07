// Fill out your copyright notice in the Description page of Project Settings.


#include "DevOnly/SGTestDamageActor.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

// Sets default values
ASGTestDamageActor::ASGTestDamageActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);
	
}

// Called when the game starts or when spawned
void ASGTestDamageActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASGTestDamageActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DrawDebugSphere(GetWorld(), GetActorLocation(), Radius, 32, Color);
	
	UGameplayStatics::ApplyRadialDamage(
		GetWorld(),
		Damage, 
		GetActorLocation(), 
		Radius, 
		nullptr, 
		{},
		this,
		nullptr, 
		DoFullDamage
	);
}

