// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_PlayerController.h"
#include "../Debug_Helpers.h"
#include "EngineUtils.h"

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

	FColor DEBUG_printColor = FColor::White;
	if (playerFaction == EAffiliation::Trojan) 
	{
		DEBUG_printColor = FColor::Cyan;
	}
	else if (playerFaction == EAffiliation::Orion)
	{
		DEBUG_printColor = FColor::Magenta;
	}
	else if (playerFaction == EAffiliation::Chiron)
	{
		DEBUG_printColor = FColor::Yellow;
	}

	// Visible log so you can confirm runtime behavior in the Output Log.
	UE_LOG(LogTemp, Warning, TEXT("CPP_PlayerController::BeginPlay - pointsOfInfluence.Num() = %d"), pointsOfInfluence.Num());
	PrintOnLevel(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("CPP_PlayerController: pointsOfInfluence.Num() = %d"), pointsOfInfluence.Num()));

	if (pointsOfInfluence.Num() > 0)
	{
		for (AControlPoint* poi : pointsOfInfluence)
		{
			PrintOnLevel(
				-1, 1.f,
				DEBUG_printColor,
				FString::Printf(
					TEXT("CPP_PlayerController: %s(%s): Control = %s, Presence = %s"),
					*poi->GetActorLabel(),
					*StaticEnum<EAffiliation>()->GetDisplayNameTextByValue((int64)poi->faction).ToString(),
					*FString::SanitizeFloat(poi->mainProperties.getControlPercentageByFaction(playerFaction)),
					*FString::FromInt(poi->orderOfBattleProperties.getShipPresenceByFaction(playerFaction))
				)
			);
		}
	}
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