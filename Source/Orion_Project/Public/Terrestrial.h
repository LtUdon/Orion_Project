// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ControlPoint.h"
#include "Terrestrial.generated.h"

/**
 * 
 */
UCLASS()
class ORION_PROJECT_API ATerrestrial : public AControlPoint
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	// Sets default values for this actor's properties
	ATerrestrial();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Station", Meta = (ToolTip = "Scale factor for ship storage boost."))
	float boostStorageScale;
};
