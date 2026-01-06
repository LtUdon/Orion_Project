// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_PlayerController.h"
#include "../Debug_Helpers.h"

ACPP_PlayerController::ACPP_PlayerController()
{
	// Set this player controller to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	isPressing = false;
	isHovering = false;
}

void ACPP_PlayerController::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACPP_PlayerController::ControlPoint_Pressed_Implementation(AActor* pressedActor)
{
	isPressing = true;
	PrintOnLevel(
		-1, 2.f, 
		FColor::Cyan, 
		FString::Printf(
			TEXT("CPP_PlayerController: isPressing set to %s from %s"), 
			*FString(isPressing ? TEXT("true") : TEXT("false")),
			*pressedActor->GetActorLabel()));
}

void ACPP_PlayerController::ControlPoint_Released_Implementation(AActor* releasedActor)
{
	isPressing = false;
	PrintOnLevel(
		-1, 2.f, 
		FColor::Blue, 
		FString::Printf(
			TEXT("CPP_PlayerController: isPressing set to %s from %s"),
			*FString(isPressing ? TEXT("true") : TEXT("false")),
			*releasedActor->GetActorLabel()));
}

void ACPP_PlayerController::ControlPoint_Hovered_Implementation(AActor* hoveredActor)
{
	isHovering = true;
	PrintOnLevel(
		-1, 2.f, 
		FColor::Magenta, 
		FString::Printf(
			TEXT("CPP_PlayerController: isHovering set to %s from %s"),
			*FString(isHovering ? TEXT("true") : TEXT("false")),
			*hoveredActor->GetActorLabel()));
}

void ACPP_PlayerController::ControlPoint_Unhovered_Implementation(AActor* unhoveredActor)
{
	isHovering = false;
	PrintOnLevel(
		-1, 2.f, 
		FColor::Purple, 
		FString::Printf(
			TEXT("CPP_PlayerController: isHovering set to %s from %s"), 
			*FString(isHovering ? TEXT("true") : TEXT("false")),
			*unhoveredActor->GetActorLabel()));
}