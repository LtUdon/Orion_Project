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
	AControlPoint::destroyRandomShip(DeltaTime);
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

	UE_LOG(
		LogTemp, 
		Log, 
		TEXT("%s: Ship unregistered. Trojan: %d, Orion: %d, Chironian: %d"), 
		*GetName(), 
		orderOfBattleProperties.presentShips_trojan,
		orderOfBattleProperties.presentShips_orion,
		orderOfBattleProperties.presentShips_chironian);
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
	else {
		// Decay actions
		float controlDecay = controlRate * deltaTime * 0.5f; // Decay is half the control rate

		if (orderOfBattleProperties.presentShips_trojan <= 0)
		{
			mainProperties.controlPercentage_trojan = FMath::Max(0.0f, mainProperties.controlPercentage_trojan - controlDecay);
		} 
		else if (orderOfBattleProperties.presentShips_orion <= 0)
		{
			mainProperties.controlPercentage_orion = FMath::Max(0.0f, mainProperties.controlPercentage_orion - controlDecay);
		}
		else if (orderOfBattleProperties.presentShips_chironian <= 0)
		{
			mainProperties.controlPercentage_chironian = FMath::Max(0.0f, mainProperties.controlPercentage_chironian - controlDecay);
		}
	}

	// Calculate target gain for each faction based on their ship presence
	float controlChange_trojan    = (orderOfBattleProperties.presentShips_trojan / totalShips) * controlRate * deltaTime;
	float controlChange_orion     = (orderOfBattleProperties.presentShips_orion / totalShips) * controlRate * deltaTime;
	float controlChange_chironian = (orderOfBattleProperties.presentShips_chironian / totalShips) * controlRate * deltaTime;
	float totalControlChange      = controlChange_trojan + controlChange_orion + controlChange_chironian;

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

	PrintOnLevel(
		-1, 0.001f,
		FColor::Green,
		FString::Printf(
			TEXT("Control: Trojan: %.2f%%, Orion: %.2f%%, Chiron: %.2f%%, Neutral: %.2f%%"),
			mainProperties.controlPercentage_trojan,
			mainProperties.controlPercentage_orion,
			mainProperties.controlPercentage_chironian,
			mainProperties.controlPercentage_neutral
		)
	);
}

void AControlPoint::destroyRandomShip(float deltaTime)
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

	// Randomly select a ship to destroy based on faction proportions
	int randomIndex = FMath::RandRange(1, totalShips);
	if (randomIndex <= orderOfBattleProperties.presentShips_trojan)
	{
		orderOfBattleProperties.presentShips_trojan = FMath::Max(0, orderOfBattleProperties.presentShips_trojan - 1);
		PrintOnLevel(
			-1, 
			5.f, 
			FColor::Cyan, 
			FString::Printf(TEXT("%s: A Trojan ship has been destroyed!"), *GetName())
		);
	}
	else if (randomIndex <= orderOfBattleProperties.presentShips_trojan + orderOfBattleProperties.presentShips_orion)
	{
		orderOfBattleProperties.presentShips_orion = FMath::Max(0, orderOfBattleProperties.presentShips_orion - 1);
		PrintOnLevel(
			-1,
			5.f,
			FColor::Magenta,
			FString::Printf(TEXT("%s: A Orion ship has been destroyed!"), *GetName())
		);
	}
	else
	{
		orderOfBattleProperties.presentShips_chironian = FMath::Max(0, orderOfBattleProperties.presentShips_chironian - 1);
		PrintOnLevel(
			-1,
			5.f,
			FColor::Yellow,
			FString::Printf(TEXT("%s: A Chironian ship has been destroyed!"), *GetName())
		);
	}
}

void AControlPoint::UpdateFaction()
{
	// No access atm
	if (mainProperties.controlPercentage_trojan == 100)
	{
		faction = EAffiliation::Trojan;
	}
	else if (mainProperties.controlPercentage_orion == 100)
	{
		faction = EAffiliation::Orion;
	}
	else if (mainProperties.controlPercentage_chironian == 100)
	{
		faction = EAffiliation::Chiron;
	}
	else 
	{
		faction = EAffiliation::None;
	}
}