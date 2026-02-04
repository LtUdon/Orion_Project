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
}

void ACPP_PlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FColor DEBUG_printColor = FColor::White;
	if (playerFaction == EAffiliation::Trojan)
	{
		DEBUG_printColor = FColor::Blue;
	}
	else if (playerFaction == EAffiliation::Orion)
	{
		DEBUG_printColor = FColor::Red;
	}
	else if (playerFaction == EAffiliation::Chiron)
	{
		DEBUG_printColor = FColor::Yellow;
	}

	if (pointsOfInfluence.Num() > 0)
	{
		for (AControlPoint* poi : pointsOfInfluence)
		{
			PrintOnLevel(
				-1, 0.001f,
				DEBUG_printColor,
				FString::Printf(
					TEXT("%s (%s): %% = %s, # = %s"),
					*poi->GetActorLabel(),                                                                        // Planet DisplayName
					*StaticEnum<EAffiliation>()->GetDisplayNameTextByValue((int64)poi->faction).ToString(),       // Planet Faction
					*FString::SanitizeFloat(poi->mainProperties.getControlPercentageByFaction(playerFaction), 2), // Control Percentage
					*FString::FromInt(poi->orderOfBattleProperties.getShipPresenceByFaction(playerFaction))       // Ship Presence
				)
			);
		}
	}
}

void ACPP_PlayerController::ControlPoint_Pressed_Implementation(AActor* pressedActor)
{
	actorPressed = pressedActor;
}

void ACPP_PlayerController::ControlPoint_Released_Implementation()
{
	actorPressed = nullptr;
}

void ACPP_PlayerController::ControlPoint_Hovered_Implementation(AActor* hoveredActor)
{
	actorHovered = hoveredActor;
}

void ACPP_PlayerController::ControlPoint_Unhovered_Implementation()
{
	actorHovered = nullptr;
}

void ACPP_PlayerController::AddPointOfInfluence(AControlPoint* pointToAdd)
{
	if (pointToAdd && !pointsOfInfluence.Contains(pointToAdd))
	{
		pointsOfInfluence.Add(pointToAdd);
	}
}

void ACPP_PlayerController::RemovePointOfInfluence(AControlPoint* pointToRemove)
{
	if (pointToRemove && pointsOfInfluence.Contains(pointToRemove))
	{
		pointsOfInfluence.Remove(pointToRemove);
	}
}

void ACPP_PlayerController::CalculateControlOverSystem()
{
	controlOverSystem = 0.f;

	// TActorIterator<AControlPoint> it(GetWorld());
	float totalSystemPoints      = 0.f;
	float playerControlledPoints = 0.f;
	for (TActorIterator<AControlPoint> it(GetWorld()); it; ++it)
	{
		totalSystemPoints += 100.f;

		// Cast to AControlPoint
		AControlPoint* poi      = *it;
		playerControlledPoints += poi->mainProperties.getControlPercentageByFaction(playerFaction);
	}

	controlOverSystem = (playerControlledPoints / totalSystemPoints) * 100.f;
}

void ACPP_PlayerController::CalculateTotalShipsInSystem()
{
	totalShipsInSystem = 0;
	for (AControlPoint* poi : pointsOfInfluence)
	{
		if (poi)
		{
			totalShipsInSystem += poi->orderOfBattleProperties.getShipPresenceByFaction(playerFaction);
		}
	}
}