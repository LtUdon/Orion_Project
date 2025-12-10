// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ControlPoint.h"
#include "Station.generated.h"

/**
 * Represents space stations that provide production boost.
 */
UCLASS()
class ORION_PROJECT_API AStation : public AControlPoint
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	// Sets default values for this actor's properties
	AStation();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Station", Meta = (ToolTip = "Scale factor for ship production boost."))
	float boostProductionModifier;
};
