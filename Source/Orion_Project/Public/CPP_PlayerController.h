// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include <../Affiliation.h>
#include "ControlPoint.h"
#include "CPP_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ORION_PROJECT_API ACPP_PlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ACPP_PlayerController();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	/* Player Interactions */
	UPROPERTY(
		EditAnywhere,
		BlueprintReadWrite,
		Category = "Player Interacts",
		Meta = (
			ToolTip = "The actor that the player has currently pressed."))
	AActor* actorPressed;

	UPROPERTY(
		EditAnywhere,
		BlueprintReadWrite,
		Category = "Player Interacts",
		Meta = (
			ToolTip = "The actor that the player is currently hovering over."))
	AActor* actorHovered;

	/* Events */
	UFUNCTION(
		BlueprintNativeEvent, 
		BlueprintCallable, 
		Category = "Events")
	void ControlPoint_Pressed(AActor* pressedActor);

	UFUNCTION(
		BlueprintNativeEvent, 
		BlueprintCallable, 
		Category = "Events")
	void ControlPoint_Released();

	UFUNCTION(
		BlueprintNativeEvent, 
		BlueprintCallable, 
		Category = "Events")
	void ControlPoint_Hovered(AActor* hoveredActor);

	UFUNCTION(
		BlueprintNativeEvent, 
		BlueprintCallable, 
		Category = "Events")
	void ControlPoint_Unhovered();

	/* Player Characteristics */
	UPROPERTY(
		EditAnywhere,
		BlueprintReadWrite,
		Category = "Player Characteristics",
		Meta = (
			ToolTip = "The player's affiliation."))
	EAffiliation playerFaction;

	// Points of Influence
	UPROPERTY(
		EditAnywhere,
		BlueprintReadWrite,
		Category = "Player Characteristics",
		Meta = (
			ToolTip = "Lists all planets that the player has ships on."))
	TArray<AControlPoint*> pointsOfInfluence;

	UFUNCTION(
		BlueprintCallable,
		Category = "Player Characteristics",
		Meta = (
			ToolTip = "Add a control point to the player's points of influence."))
	void AddPointOfInfluence(AControlPoint* pointToAdd);

	UFUNCTION(
		BlueprintCallable,
		Category = "Player Characteristics",
		Meta = (
			ToolTip = "Remove a control point from the player's points of influence."))
	void RemovePointOfInfluence(AControlPoint* pointToRemove);

	UPROPERTY(
		EditAnywhere,
		BlueprintReadOnly,
		Meta = (
			ToolTip = "Index of the last added point of influence."))
	int32 POI_indexAdded;

	UPROPERTY(
		EditAnywhere,
		BlueprintReadOnly,
		Meta = (
			ToolTip = "Index of the last removed point of influence.")
	)
	int32 POI_indexRemoved;

	// Overall Control
	UPROPERTY(
		EditAnywhere,
		BlueprintReadWrite,
		Category = "Player Characteristics",
		Meta = (
			ToolTip = "The player's overall control over the current system."))
	float controlOverSystem;

	UFUNCTION(
		BlueprintCallable,
		Category = "Player Characteristics",
		Meta = (
			ToolTip = "Calculate the player's overall control over the current system."))
	void CalculateControlOverSystem();

	// Total Ships in System
	UPROPERTY(
		EditAnywhere,
		BlueprintReadWrite,
		Category = "Player Characteristics",
		Meta = (
			ToolTip = "The number of ships present in the entire system."))
	int32 totalShipsInSystem;

	UFUNCTION(
		BlueprintCallable,
		Category = "Player Characteristics",
		Meta = (
			ToolTip = "Calculate the total number of ships present in the entire system."))
	void CalculateTotalShipsInSystem();
};
