// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_PlayerController.h"
#include "../Debug_Helpers.h"

ACPP_PlayerController::ACPP_PlayerController()
{
	// Set this player controller to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ACPP_PlayerController::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACPP_PlayerController::ControlPoint_Pressed_Implementation(AActor* pressedActor)
{
	PrintOnLevel(-1, 2.f, FColor::Cyan, FString::Printf(TEXT("CPP_PlayerController: %s PRESSED"), *pressedActor->GetName()));
}

void ACPP_PlayerController::ControlPoint_Released_Implementation(AActor* releasedActor)
{
	PrintOnLevel(-1, 2.f, FColor::Blue, FString::Printf(TEXT("CPP_PlayerController: %s RELEASED"), *releasedActor->GetName()));
}

void ACPP_PlayerController::ControlPoint_Hovered_Implementation(AActor* hoveredActor)
{
	PrintOnLevel(-1, 2.f, FColor::Magenta, FString::Printf(TEXT("CPP_PlayerController: %s HOVERED"), *hoveredActor->GetName()));
}