// Fill out your copyright notice in the Description page of Project Settings.


#include "Station.h"

AStation::AStation()
{
	PrimaryActorTick.bCanEverTick = true;

	// Default values
	boostProductionModifier = 1.5f;
}

void AStation::BeginPlay()
{
	Super::BeginPlay();
}

void AStation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}