// Fill out your copyright notice in the Description page of Project Settings.


#include "ControlPoint.h"

AControlPoint::AControlPoint()
{
	FString Format = FString::Printf(TEXT(""));

	PrimaryActorTick.bCanEverTick = true;

	// Default values
	controlRate                 = 5.0f;
	controlPercentage_trojan    = 0.0f;
	controlPercentage_orion     = 0.0f;
	controlPercentage_chironian = 0.0f;

	// Order of Battle defaults
	productionRate      = 2.0f;
	maxShipsToProduce   = 50;
	presentShips_trojan = 0;
	presentShips_orion  = 0;

	// Create selector widget and set as child to the RootComponent (OrbiterMesh)
	SelectorWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Selector Widget"));
	SelectorWidget->SetupAttachment(RootComponent);

	static ConstructorHelpers::FClassFinder<UUserWidget> WidgetAsset(TEXT("/Game/Main/Widgets/W_ControlPoint.W_ControlPoint_C"));
	if (WidgetAsset.Succeeded())
	{
		Format = FString::Printf(TEXT("Widget asset for Control Point found: %s"), *WidgetAsset.Class->GetName());
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, Format);
		}
		WidgetClass = WidgetAsset.Class;
		SelectorWidget->SetWidgetClass(WidgetClass);
	}
	else
	{
		Format = FString::Printf(TEXT("Widget asset for Control Point NOT found!"));
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, Format);
		}
	}
}

void AControlPoint::BeginPlay()
{
	Super::BeginPlay();
	if (SelectorWidget && WidgetClass)
	{
		SelectorWidget->SetWidgetClass(WidgetClass);
		SelectorWidget->SetWidgetSpace(EWidgetSpace::Screen);
	}
}

// Called every frame
void AControlPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	controlPercentage_neutral = getControlPercentage_neutral();
}

float AControlPoint::getControlPercentage_neutral()
{
	float totalControlled = controlPercentage_trojan + controlPercentage_orion + controlPercentage_chironian;
	float neutralPercentage = 100.0f - totalControlled;
	return neutralPercentage;
}

void AControlPoint::RegisterShip(EAffiliation shipFaction)
{
	switch (shipFaction)
	{
	case EAffiliation::Trojan:
		presentShips_trojan++;
		break;
	case EAffiliation::Orion:
		presentShips_orion++;
		break;
	case EAffiliation::Chiron:
		presentShips_chironian++;
		break;
	default:
		break;
	}

	UE_LOG(LogTemp, Log, TEXT("%s: Ship registered. Trojan: %d, Orion: %d, Chiron: %d"), *GetName(), presentShips_trojan, presentShips_orion, presentShips_chironian);
}

void AControlPoint::UnregisterShip(EAffiliation shipAffiliation)
{
	switch (shipAffiliation)
	{
		case EAffiliation::Trojan:
			presentShips_trojan    = FMath::Max(0, presentShips_trojan - 1);
			break;
		case EAffiliation::Orion:
			presentShips_orion     = FMath::Max(0, presentShips_orion - 1);
			break;
		case EAffiliation::Chiron:
			presentShips_chironian = FMath::Max(0, presentShips_chironian - 1);
			break;
		default:
			break;
	}

	UE_LOG(LogTemp, Log, TEXT("%s: Ship unregistered. Trojan: %d, Orion: %d, Chironian: %d"), *GetName(), presentShips_trojan, presentShips_orion, presentShips_chironian);
}

int AControlPoint::GetShipCount(EAffiliation shipFaction) const
{
	switch (shipFaction)
	{
		case EAffiliation::Trojan:
			return presentShips_trojan;
		case EAffiliation::Orion:
			return presentShips_orion;
		case EAffiliation::Chiron:
			return presentShips_chironian;
		default:
			return 0;
	}
}