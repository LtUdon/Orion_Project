// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Orbiter.h"
#include "Components/WidgetComponent.h"
#include "ControlPoint_Structs.h"
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

	UPROPERTY(
		EditAnywhere, 
		BlueprintReadWrite, 
		Category = "Control Point", 
		Meta = (
			ToolTip = "The rate at which the planet can be conquered."))
	float controlRate;

	/* Widget Properties */
	UPROPERTY(
		VisibleAnywhere,
		BlueprintReadWrite,
		Category = "Control Point",
		Meta = (
			ToolTip = "Set up the characteristics of the widget."))
	UWidgetComponent* SelectorWidget;

	UPROPERTY(
		EditDefaultsOnly,
		BlueprintReadWrite,
		Category = "Control Point")
	TSubclassOf<UUserWidget> WidgetClass;

	/* Main Properties */
	UPROPERTY(
		VisibleAnywhere,
		BlueprintReadWrite,
		Category = "Control Point",
		Meta = (
			ToolTip = "Main properties of the control point."))
	FControlPoint_Main mainProperties;

	UFUNCTION(
		BlueprintCallable,
		Category = "Control Point",
		Meta = (
			ToolTip = "Update control percentages based on control rate when ships are present."))
	void UpdateControlPercentages(float deltaTime);

	UFUNCTION(
		BlueprintCallable,
		Category = "Control Point", 
		Meta = (
			ToolTip = "Increase control of the fully present faction."))
	void GainControl(EAffiliation factionToGain, float amount);

	UFUNCTION(
		BlueprintCallable,
		Category = "Control Point",
		Meta = (
			ToolTip = "Decrease control of the fully present faction."))
	void DecayControl(EAffiliation factionToLose, float amount);

	UFUNCTION(
		BlueprintCallable,
		Category = "Control Point",
		Meta = (
			ToolTip = "Maintains full control by present faction. Only applicable if the Control Point's faction is the same as the present faction."))
	void SetFullControl(EAffiliation controllingFaction);

	UFUNCTION(
		BlueprintCallable,
		Category = "Control Point",
		Meta = (
			ToolTip = "Normalize control percentages."))
	void NormalizeControlPercentages();

	UFUNCTION(
		BlueprintCallable,
		Category = "Control Point",
		Meta = (
			ToolTip = "Return the number of factions present."))
	int GetNumFactionsPresent() const;

	/* Order of Battle Properties */
	UPROPERTY(
		EditAnywhere,
		BlueprintReadWrite,
		Category = "Control Point",
		Meta = (
			ToolTip = "Order of battle properties of the control point."))
	FOrderOfBattle orderOfBattleProperties;

	UPROPERTY(
		EditAnywhere,
		BlueprintReadWrite, 
		Category = "Control Point: Order of Battle", 
		Meta = (
			ToolTip = "The rate at which a control point can produce ships of the affiliation that has captured it."))
	float productionRate;

	UPROPERTY(
		EditAnywhere, 
		BlueprintReadWrite, 
		Category = "Control Point: Order of Battle", 
		Meta = (
			ToolTip = "Maximum number of ships that can be produced on a control point."))
	int maxShipsToProduce;

	UFUNCTION(
		BlueprintCallable, 
		Category = "Control Point: Order of Battle", 
		Meta = (
			ToolTip = "Register a ship when it begins orbiting the actor."))
	void RegisterShip(EAffiliation shipFaction);

	UFUNCTION(
		BlueprintCallable, 
		Category = "Control Point: Order of Battle", 
		Meta = (
			ToolTip = "Unregister a ship when it leaves the orbiter its orbiting."))
	void UnregisterShip(EAffiliation shipFaction);

	UFUNCTION(
		BlueprintCallable, 
		Category = "Control Point: Order of Battle", 
		Meta = (
			ToolTip = "Retrieve numerical of ships station on the actor based on the ship(s) faction."))
	int GetShipCount(EAffiliation shipFaction) const;

	UFUNCTION(
		BlueprintCallable,
		Category = "Control Point: Order of Battle",
		Meta = (
			ToolTip = "Randomly destroy a ship when more than one faction is present on a control point."))
	void DestroyRandomShip(float deltaTime);

	UFUNCTION(
		BlueprintCallable,
		Category = "Control Point: Order of Battle",
		Meta = (
			ToolTip = "Update affiliation when a faction assumes full control."
			)
	)
	void UpdateFaction();

	UFUNCTION(
		Blueprintcallable,
		Category = "Control Point: Order of Battle",
		Meta = (
			ToolTip = "Return the faction of ships present on the control point. Only applicable if the faction has full presence."))
	EAffiliation GetFullPresentFaction() const;

	// The object's distance from camera for widget draw size configuration
	UPROPERTY(
		Transient)
	float distanceFromCamera = 0.0f;
};
