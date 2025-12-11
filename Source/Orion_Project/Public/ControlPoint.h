// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Orbiter.h"
#include "../Affiliation.h"
#include "ControlPoint.generated.h"

/**
 * 
 */
UCLASS()
class ORION_PROJECT_API AControlPoint : public AOrbiter
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	// Sets default values for this actor's properties
	AControlPoint();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control Point", Meta = (ToolTip = "The rate at which the planet can be conquered."))
	float controlRate;

	// Control percentages for each faction
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Control Point", Meta = (ToolTip = "Trojan's control percentage of the planet."))
	float controlPercentage_trojan;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Control Point", Meta = (ToolTip = "Orion's control percentage of the planet."))
	float controlPercentage_orion;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Control Point", Meta = (ToolTip = "Chironian's control percentage of the planet."))
	float controlPercentage_chironian;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Control Point", Meta = (ToolTip = "Neutrality percentage of the planet."))
	float controlPercentage_neutral;

	float getControlPercentage_neutral();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control Point", Meta = (ToolTip = "The current controlling faction of the planet."))
	EAffiliation controllingFaction;

	// Order of Battle properties

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control Point: Order of Battle", Meta = (ToolTip = "The rate at which a control point can produce ships of the affiliation that has captured it."))
	float productionRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control Point: Order of Battle", Meta = (ToolTip = "Maximum number of ships that can be produced on a control point."))
	int maxShipsToProduce;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Control Point: Order of Battle", Meta = (ToolTip = "Number of Trojan ships on the control point."))
	int presentShips_trojan;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Control Point: Order of Battle", Meta = (ToolTip = "Number of Orion ships on the control point."))
	int presentShips_orion;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Control Point: Order of Battle", Meta = (ToolTip = "Number of Chironian ships on the control point."))
	int presentShips_chironian;
};
