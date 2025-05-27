#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EAffiliation : uint8
{
    None    UMETA(DisplayName = "None"),
    Trojan  UMETA(DisplayName = "Trojan"),
    Orion   UMETA(DisplayName = "Orion")
};