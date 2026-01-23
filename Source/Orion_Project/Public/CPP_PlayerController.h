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

	UPROPERTY(
		EditAnywhere,
		BlueprintReadWrite,
		Category = "Player Characteristics",
		Meta = (
			ToolTip = "Lists all planets that the player has ships on."))
	TArray<AControlPoint*> pointsOfInfluence;

	UPROPERTY(
		EditAnywhere,
		BlueprintReadOnly,
		Category = "Player Characteristics",
		Meta = (
			ToolTip = "The player's overall control over the current system."))
	float controlOverSystem;
};
