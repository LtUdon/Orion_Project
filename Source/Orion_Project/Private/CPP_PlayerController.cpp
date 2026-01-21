// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_PlayerController.h"
#include "../Debug_Helpers.h"

ACPP_PlayerController::ACPP_PlayerController()
{
	PrimaryActorTick.bCanEverTick = true;

	actorPressed  = nullptr;
	actorHovered  = nullptr;
	playerFaction = EAffiliation::None;
}

void ACPP_PlayerController::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACPP_PlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	PrintOnLevel(
		-1, 0.001f, 
		FColor::Green, 
		FString::Printf(
			TEXT("CPP_PlayerController: playerFaction = %s"),
			*StaticEnum<EAffiliation>()->GetDisplayNameTextByValue((int64)playerFaction).ToString()
		)
	);
}

void ACPP_PlayerController::ControlPoint_Pressed_Implementation(AActor* pressedActor)
{
	actorPressed = pressedActor;
	PrintOnLevel(
		-1, 2.f, 
		FColor::Cyan, 
		FString::Printf(
			TEXT("CPP_PlayerController: actorPressed = %s"), 
			*pressedActor->GetActorLabel()
		)
	);
}

void ACPP_PlayerController::ControlPoint_Released_Implementation()
{
	actorPressed = nullptr;
	PrintOnLevel(
		-1, 2.f, 
		FColor::Blue, 
		FString::Printf(
			TEXT("CPP_PlayerController: actorPressed = %s"),
			IsValid(actorPressed) && actorPressed ? *actorPressed->GetActorLabel() : TEXT("NONE")
		)
	);
}

void ACPP_PlayerController::ControlPoint_Hovered_Implementation(AActor* hoveredActor)
{
	actorHovered = hoveredActor;
}

void ACPP_PlayerController::ControlPoint_Unhovered_Implementation()
{
	actorHovered = nullptr;
}