// Fill out your copyright notice in the Description page of Project Settings.


#include "ControlPoint.h"
#include "../Debug_Helpers.h"


AControlPoint::AControlPoint()
{
	PrimaryActorTick.bCanEverTick = true;
	FString Format = FString::Printf(TEXT(""));

	// Default values
	controlRate = 5.0f;
	mainProperties.controlPercentage_trojan    = 0.0f;
	mainProperties.controlPercentage_orion     = 0.0f;
	mainProperties.controlPercentage_chironian = 0.0f;

	// Order of Battle defaults
	productionRate    = 2.0f;
	maxShipsToProduce = 50;
	orderOfBattleProperties.presentShips_trojan    = 0;
	orderOfBattleProperties.presentShips_orion     = 0;
	orderOfBattleProperties.presentShips_chironian = 0;

	// Create selector widget and set as child to the RootComponent (OrbiterMesh)
	SelectorWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Selector Widget"));
	SelectorWidget->SetupAttachment(RootComponent);

	static ConstructorHelpers::FClassFinder<UUserWidget> WidgetAsset(TEXT("/Game/Main/Widgets/W_ControlPoint.W_ControlPoint_C"));
	if (WidgetAsset.Succeeded())
	{
		WidgetClass = WidgetAsset.Class;
		SelectorWidget->SetWidgetClass(WidgetClass);
	}
}

void AControlPoint::BeginPlay()
{
	Super::BeginPlay();
	FString Format = FString::Printf(TEXT(""));

	if (SelectorWidget)
	{
		SelectorWidget->InitWidget(); // Force initialization of the widget
		SelectorWidget->SetWidgetClass(WidgetClass);
		SelectorWidget->SetWidgetSpace(EWidgetSpace::Screen);

		// Give the widget (W_ControlPoint) a reference to this control point actor
		UUserWidget* Widget = SelectorWidget->GetWidget();
		if (Widget)
		{
			FObjectProperty* Property = FindFProperty<FObjectProperty>(Widget->GetClass(), TEXT("OwnerActor"));
			if (Property)
			{
				Property->SetObjectPropertyValue_InContainer(Widget, this);
			}
		}
	}
}

// Called every frame
void AControlPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AControlPoint::UpdateControlPercentages(DeltaTime);
	AControlPoint::DestroyRandomShip(DeltaTime);
	AControlPoint::UpdateFaction();
}

void AControlPoint::RegisterShip(EAffiliation shipFaction)
{
	switch (shipFaction)
	{
	case EAffiliation::Trojan:
		orderOfBattleProperties.presentShips_trojan++;
		break;
	case EAffiliation::Orion:
		orderOfBattleProperties.presentShips_orion++;
		break;
	case EAffiliation::Chiron:
		orderOfBattleProperties.presentShips_chironian++;
		break;
	default:
		break;
	}

	UE_LOG(
		LogTemp, 
		Log, 
		TEXT("%s: Ship registered. Trojan: %d, Orion: %d, Chiron: %d"), 
		*GetName(), 
		orderOfBattleProperties.presentShips_trojan,
		orderOfBattleProperties.presentShips_orion,
		orderOfBattleProperties.presentShips_chironian);
}

void AControlPoint::UnregisterShip(EAffiliation shipAffiliation)
{
	switch (shipAffiliation)
	{
		case EAffiliation::Trojan:
			orderOfBattleProperties.presentShips_trojan    = FMath::Max(0, orderOfBattleProperties.presentShips_trojan - 1);
			break;
		case EAffiliation::Orion:
			orderOfBattleProperties.presentShips_orion     = FMath::Max(0, orderOfBattleProperties.presentShips_orion - 1);
			break;
		case EAffiliation::Chiron:
			orderOfBattleProperties.presentShips_chironian = FMath::Max(0, orderOfBattleProperties.presentShips_chironian - 1);
			break;
		default:
			break;
	}
}

int AControlPoint::GetShipCount(EAffiliation shipFaction) const
{
	switch (shipFaction)
	{
		case EAffiliation::Trojan:
			return orderOfBattleProperties.presentShips_trojan;
		case EAffiliation::Orion:
			return orderOfBattleProperties.presentShips_orion;
		case EAffiliation::Chiron:
			return orderOfBattleProperties.presentShips_chironian;
		default:
			return 0;
	}
}

void AControlPoint::UpdateControlPercentages(float deltaTime)
{
	orderOfBattleProperties.updateTotalShips();
	float totalShips = static_cast<float>(orderOfBattleProperties.presentShips_total);

	if (totalShips <= 0)
	{
		return; // No ships present, no control change
	}

	// Calculate target gain for each faction based on their ship presence
	float controlChange_trojan = 0.0f;
	float controlChange_orion = 0.0f;
	float controlChange_chironian = 0.0f;
	if (orderOfBattleProperties.presentShips_trojan > 0)
	{
	    controlChange_trojan = (orderOfBattleProperties.presentShips_trojan / totalShips) * controlRate * deltaTime;
	} 
	else
	{
		controlChange_trojan = -1.f * controlRate * deltaTime;
	}

	if (orderOfBattleProperties.presentShips_orion > 0)
	{
		controlChange_orion = (orderOfBattleProperties.presentShips_orion / totalShips) * controlRate * deltaTime;
	} 
	else
	{
		controlChange_orion = -1.f * controlRate * deltaTime;
	}

	if (orderOfBattleProperties.presentShips_chironian > 0)
	{
		controlChange_chironian = (orderOfBattleProperties.presentShips_chironian / totalShips) * controlRate * deltaTime;
	} 
	else
	{
		controlChange_chironian = -1.f * controlRate * deltaTime;
	}
	float totalControlChange = controlChange_trojan + controlChange_orion + controlChange_chironian;

	mainProperties.controlPercentage_neutral = mainProperties.getControlPercentage_neutral();

	if (totalControlChange > mainProperties.controlPercentage_neutral)
	{
		// Scale down the control changes proportionally
		float scale              = mainProperties.controlPercentage_neutral / totalControlChange;
		controlChange_trojan    *= scale;
		controlChange_orion     *= scale;
		controlChange_chironian *= scale;
	}

	// Apply control changes
	mainProperties.controlPercentage_trojan    += controlChange_trojan;
	mainProperties.controlPercentage_orion     += controlChange_orion;
	mainProperties.controlPercentage_chironian += controlChange_chironian;

	// Recalculate neutral (should now be correct)
	mainProperties.controlPercentage_neutral = mainProperties.getControlPercentage_neutral();

	// Clamp everything to be safe
	mainProperties.controlPercentage_trojan    = FMath::Clamp(mainProperties.controlPercentage_trojan, 0.0f, 100.0f);
	mainProperties.controlPercentage_orion     = FMath::Clamp(mainProperties.controlPercentage_orion, 0.0f, 100.0f);
	mainProperties.controlPercentage_chironian = FMath::Clamp(mainProperties.controlPercentage_chironian, 0.0f, 100.0f);
	mainProperties.controlPercentage_neutral   = FMath::Clamp(mainProperties.controlPercentage_neutral, 0.0f, 100.0f);

	mainProperties.controlPercentage_neutral = mainProperties.getControlPercentage_neutral();

	PrintOnLevel(
		-1, 0.001f,
		FColor::Green,
		FString::Printf(
			TEXT("%s: Trojan: %.2f%%, Orion: %.2f%%, Chiron: %.2f%%, Neutral: %.2f%%"),
			*GetActorLabel(),
			mainProperties.controlPercentage_trojan,
			mainProperties.controlPercentage_orion,
			mainProperties.controlPercentage_chironian,
			mainProperties.controlPercentage_neutral
		)
	);
}

void AControlPoint::DestroyRandomShip(float deltaTime)
{
	// Check if more than one faction is present
	int factionsPresent = 0;
	if (orderOfBattleProperties.presentShips_trojan > 0)    factionsPresent++;
	if (orderOfBattleProperties.presentShips_orion > 0)     factionsPresent++;
	if (orderOfBattleProperties.presentShips_chironian > 0) factionsPresent++;
	if (factionsPresent <= 1)
	{
		return; // Only one or no faction present, no ship destruction needed
	}
	// Determine total ships present
	int totalShips = orderOfBattleProperties.presentShips_trojan +
					 orderOfBattleProperties.presentShips_orion +
					 orderOfBattleProperties.presentShips_chironian;
	if (totalShips <= 0)
	{
		return; // No ships to destroy
	}

	// Set up destruction selection by reversing proportions by ship count
	float deleteFactor_trojan    = (totalShips - orderOfBattleProperties.presentShips_trojan) / static_cast<float>(totalShips);
	float deleteFactor_orion     = (totalShips - orderOfBattleProperties.presentShips_orion) / static_cast<float>(totalShips);
	float deleteFactor_chironian = (totalShips - orderOfBattleProperties.presentShips_chironian) / static_cast<float>(totalShips);

	float totalDeleteFactor = deleteFactor_trojan + deleteFactor_orion + deleteFactor_chironian;

	// Randomly select a faction to destroy a ship from
	float randomValue = FMath::FRandRange(0.0f, totalDeleteFactor);
	if (randomValue < deleteFactor_trojan)
	{
		UnregisterShip(EAffiliation::Trojan);

	}
	else if (randomValue < deleteFactor_trojan + deleteFactor_orion)
	{
		UnregisterShip(EAffiliation::Orion);
	}
	else
	{
		UnregisterShip(EAffiliation::Chiron);
	}
}

void AControlPoint::UpdateFaction()
{
	if (mainProperties.controlPercentage_trojan == 100.0f)
	{
		faction = EAffiliation::Trojan;
	}
	else if (mainProperties.controlPercentage_orion == 100.0f)
	{
		faction = EAffiliation::Orion;
	}
	else if (mainProperties.controlPercentage_chironian == 100.0f)
	{
		faction = EAffiliation::Chiron;
	}
	else 
	{
		faction = EAffiliation::None;
	}
}