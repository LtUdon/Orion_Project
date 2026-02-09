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

	static ConstructorHelpers::FClassFinder<UUserWidget> WidgetAsset(TEXT("/Game/Main/Widgets/W_ControlPoint/W_ControlPoint_Icon.W_ControlPoint_Icon_C"));
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
		/* Nothing should happen */
		return;
	}

	int32 numFactionsPresent = GetNumFactionsPresent();

	if (numFactionsPresent > 1)
	{
		return;
	}

	EAffiliation presentFaction = GetFullPresentFaction();
	if (presentFaction == EAffiliation::None)
	{
		return;
	}

	float controlIncrease = controlRate * deltaTime; // Per tick

	if (AOrbiter::faction == EAffiliation::None)
	{
		GainControl(presentFaction, controlIncrease);
	}
	else if (AOrbiter::faction == presentFaction)
	{
		SetFullControl(presentFaction);
	}
	else
	{
		DecayControl(AOrbiter::faction, controlIncrease);
	}

	NormalizeControlPercentages();
}

void AControlPoint::GainControl(EAffiliation factionToGain, float amount)
{
	switch (factionToGain)
	{
	case EAffiliation::Trojan:
		mainProperties.controlPercentage_trojan += amount;
		mainProperties.controlPercentage_trojan  = FMath::Clamp(mainProperties.controlPercentage_trojan, 0.f, 100.f);
		break;
	case EAffiliation::Orion:
		mainProperties.controlPercentage_orion += amount;
		mainProperties.controlPercentage_orion  = FMath::Clamp(mainProperties.controlPercentage_orion, 0.f, 100.f);
		break;
	case EAffiliation::Chiron:
		mainProperties.controlPercentage_chironian += amount;
		mainProperties.controlPercentage_chironian  = FMath::Clamp(mainProperties.controlPercentage_chironian, 0.f, 100.f);
		break;
	default:
		break;
	}
}

void AControlPoint::DecayControl(EAffiliation factionToLose, float amount)
{
	switch (factionToLose)
	{
	case EAffiliation::Trojan:
		mainProperties.controlPercentage_trojan -= amount;
		mainProperties.controlPercentage_trojan  = FMath::Max(mainProperties.controlPercentage_trojan, 0.f);
		break;
	case EAffiliation::Orion:
		mainProperties.controlPercentage_orion -= amount;
		mainProperties.controlPercentage_orion  = FMath::Max(mainProperties.controlPercentage_orion, 0.f);
		break;
	case EAffiliation::Chiron:
		mainProperties.controlPercentage_chironian -= amount;
		mainProperties.controlPercentage_chironian  = FMath::Max(mainProperties.controlPercentage_chironian, 0.f);
		break;
	default:
		break;
	}
}

void AControlPoint::SetFullControl(EAffiliation controllingFaction)
{
	mainProperties.controlPercentage_trojan    = (controllingFaction == EAffiliation::Trojan) ? 100.f : 0.f;
	mainProperties.controlPercentage_orion     = (controllingFaction == EAffiliation::Orion)  ? 100.f : 0.f;
	mainProperties.controlPercentage_chironian = (controllingFaction == EAffiliation::Chiron) ? 100.f : 0.f;
}

void AControlPoint::NormalizeControlPercentages()
{
	float total = mainProperties.controlPercentage_trojan + 
				  mainProperties.controlPercentage_orion + 
				  mainProperties.controlPercentage_chironian;

	if (FMath::IsNearlyEqual(total, 100.f, 0.01f))
	{
		return;
	}

	mainProperties.controlPercentage_neutral = FMath::Clamp(100.f - total, 0.f, 100.f);

	// If total exceeds 100%, scale accordingly
	if (total > 100.0f)
	{
		float scale = 100.f / total;
		mainProperties.controlPercentage_trojan    *= scale;
		mainProperties.controlPercentage_orion     *= scale;
		mainProperties.controlPercentage_chironian *= scale;
		mainProperties.controlPercentage_neutral    = 0.f;
	}

	mainProperties.controlPercentage_trojan    = FMath::Clamp(mainProperties.controlPercentage_trojan, 0.f, 100.f);
	mainProperties.controlPercentage_orion     = FMath::Clamp(mainProperties.controlPercentage_orion, 0.f, 100.f);
	mainProperties.controlPercentage_chironian = FMath::Clamp(mainProperties.controlPercentage_chironian, 0.f, 100.f);
}

int AControlPoint::GetNumFactionsPresent() const
{
	int factionsPresent = 0;
	if (orderOfBattleProperties.presentShips_trojan > 0)    factionsPresent++;
	if (orderOfBattleProperties.presentShips_orion > 0)     factionsPresent++;
	if (orderOfBattleProperties.presentShips_chironian > 0) factionsPresent++;
	return factionsPresent;
}

void AControlPoint::DestroyRandomShip(float deltaTime)
{
	// Check if more than one faction is present
	if (GetNumFactionsPresent() <= 1)
	{
		return;
	}
	
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

EAffiliation AControlPoint::GetFullPresentFaction() const
{
	if (orderOfBattleProperties.presentShips_trojan > 0)
	{
		return EAffiliation::Trojan;
	}
	else if (orderOfBattleProperties.presentShips_orion > 0)
	{
		return EAffiliation::Orion;
	}
	else if (orderOfBattleProperties.presentShips_chironian > 0)
	{
		return EAffiliation::Chiron;
	}
	else
	{
		return EAffiliation::None;
	}
}