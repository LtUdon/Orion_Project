#pragma once

#include "CoreMinimal.h"

inline void PrintOnLevel(int32 Key, float Duration, FColor Color, const FString& Message)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(Key, Duration, Color, Message);
	}
}
