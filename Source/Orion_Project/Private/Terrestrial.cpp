// Fill out your copyright notice in the Description page of Project Settings.


#include "Terrestrial.h"

ATerrestrial::ATerrestrial()
{
	PrimaryActorTick.bCanEverTick = true;

	// Default values
	boostStorageModifier = 1.5f;

	// DEBUG LOG
	FString Format = FString::Printf(TEXT(""));

	// Modify values of max ship storage of production
	maxShipsToProduce = static_cast<int>(maxShipsToProduce * boostStorageModifier);
}

void ATerrestrial::BeginPlay()
{
	Super::BeginPlay();
}

void ATerrestrial::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}