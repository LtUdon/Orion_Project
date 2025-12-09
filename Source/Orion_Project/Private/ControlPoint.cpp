// Fill out your copyright notice in the Description page of Project Settings.

#include "ControlPoint.h"

AControlPoint::AControlPoint()
{
	PrimaryActorTick.bCanEverTick = true;

	// Default values
	controlRate = 5.0f;
	controlPercentage_trojan    = 0.0f;
	controlPercentage_orion     = 0.0f;
	controlPercentage_chironian = 0.0f;
	controllingFaction = EAffiliation::None;
	// Order of Battle defaults
	maxStationedShips = 50;
	productionRate    = 2.0f;
	presentShips_trojan = 0;
	presentShips_orion  = 0;
}

void AControlPoint::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AControlPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	controlPercentage_neutral = getControlPercentage_neutral();
}

float AControlPoint::getControlPercentage_neutral()
{
	float totalControlled = controlPercentage_trojan + controlPercentage_orion + controlPercentage_chironian;
	float neutralPercentage = 100.0f - totalControlled;
	return neutralPercentage;
}