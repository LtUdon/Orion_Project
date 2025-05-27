// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Affiliation.generated.h"

UENUM(BlueprintType)             // Exposes the enum to UE's reflection system, making it accessible in Blueprints.
enum class EAffiliation : uint8 // 'uint8' is required for Blueprint compatibility
{
	None	UMETA(DisplayName = "None"),
	Trojan	UMETA(DisplayName = "Trojan"),
	Orion	UMETA(DisplayName = "Orion")
};
