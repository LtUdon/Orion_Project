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

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Events")
	void ControlPoint_Pressed(AActor* pressedActor);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Events")
	void ControlPoint_Released(AActor* releasedActor);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Events")
	void ControlPoint_Hovered(AActor* hoveredActor);
};
