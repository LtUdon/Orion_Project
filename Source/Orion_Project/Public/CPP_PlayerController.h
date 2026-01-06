// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
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

protected:
	virtual void BeginPlay() override;

	UPROPERTY(
		EditAnywhere,
		BlueprintReadWrite,
		Category = "Player Interacts",
		Meta = (
			ToolTip = "The actor that the player has currently pressed."
			)
	)
	AActor* actorPressed;

	UPROPERTY(
		EditAnywhere,
		BlueprintReadWrite,
		Category = "Player Interacts",
		Meta = (
			ToolTip = "The actor that the player is currently hovering over."
			)
	)
	AActor* actorHovered;

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
};
