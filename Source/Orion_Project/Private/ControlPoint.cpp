// Fill out your copyright notice in the Description page of Project Settings.


#include "ControlPoint.h"


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

	mainProperties.controlPercentage_neutral = mainProperties.getControlPercentage_neutral();
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