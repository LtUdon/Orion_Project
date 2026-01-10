// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ControlPoint_Structs.generated.h"

// For forward declarations
class AControlPoint;

/**
 *
 */
USTRUCT(BlueprintType)
struct FControlPoint_Main
{
	GENERATED_BODY()

	// Control percentages for each faction
	UPROPERTY(
		VisibleAnywhere,
		BlueprintReadWrite,
		Category = "Main",
		Meta = (
			ClampMin = "0.0",
			ClampMax = "100.0",
			ToolTip = "Trojan's control percentage of the planet."))
	float controlPercentage_trojan;

	UPROPERTY(
		VisibleAnywhere,
		BlueprintReadWrite,
		Category = "Main",
		Meta = (
			ClampMin = "0.0",
			ClampMax = "100.0",
			ToolTip = "Orion's control percentage of the planet."))
	float controlPercentage_orion;

	UPROPERTY(
		VisibleAnywhere,
		BlueprintReadWrite,
		Category = "Main",
		Meta = (
			ClampMin = "0.0",
			ClampMax = "100.0",
			ToolTip = "Chironian's control percentage of the planet."))
	float controlPercentage_chironian;

	UPROPERTY(
		VisibleAnywhere,
		BlueprintReadWrite,
		Category = "Main",
		Meta = (
			ClampMin = "0.0",
			ClampMax = "100.0",
			ToolTip = "Neutrality percentage of the planet."))
	float controlPercentage_neutral;

	// Default constructor
	FControlPoint_Main():
	    controlPercentage_trojan(0.f),
		controlPercentage_orion(0.f),
		controlPercentage_chironian(0.f),
		controlPercentage_neutral(100.f)
	{}

	float getControlPercentage_neutral()
	{
		return 100.f - (controlPercentage_trojan + controlPercentage_orion + controlPercentage_chironian);
	}
};

/**
 * Order of battle
 */
USTRUCT(BlueprintType)
struct FOrderOfBattle
{
	GENERATED_BODY()

	UPROPERTY(
		EditAnywhere,
		BlueprintReadWrite,
		Category = "Order of Battle",
		Meta = (
			ToolTip = "Number of Trojan ships on the control point."))
	int32 presentShips_trojan;

	UPROPERTY(
		EditAnywhere,
		BlueprintReadWrite,
		Category = "Order of Battle",
		Meta = (ToolTip = "Number of Orion ships on the control point."))
	int32 presentShips_orion;

	UPROPERTY(
		EditAnywhere,
		BlueprintReadWrite,
		Category = "Order of Battle",
		Meta = (ToolTip = "Number of Chironian ships on the control point."))
	int32 presentShips_chironian;

	UPROPERTY(
		EditAnywhere,
		BlueprintReadWrite,
		Category = "Order of Battle",
		Meta = (
			ToolTip = "Calculated number of total ships on the control point."))
	int32 presentShips_total;

	// Default constructor
	FOrderOfBattle() :
		presentShips_trojan(0),
		presentShips_orion(0),
		presentShips_chironian(0),
		presentShips_total(0)
	{}

	void updateTotalShips()
	{
		presentShips_total = presentShips_trojan + presentShips_orion + presentShips_chironian;
	}
};