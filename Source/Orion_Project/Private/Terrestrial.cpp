// Fill out your copyright notice in the Description page of Project Settings.


#include "Terrestrial.h"

ATerrestrial::ATerrestrial()
{
	PrimaryActorTick.bCanEverTick = true;

	// Default values
	boostStorageScale = 1.5f;
}

void ATerrestrial::BeginPlay()
{
	Super::BeginPlay();
}

void ATerrestrial::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}