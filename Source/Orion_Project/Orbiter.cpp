// Fill out your copyright notice in the Description page of Project Settings.


#include "Orbiter.h"

// Sets default values
AOrbiter::AOrbiter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mesh"));
	mesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	// Default values
	revolutionSpeed = 1.0f;
	rotationSpeed = 1.0f;
	range = 10.0f;          // Orbit radius
}

// Called when the game starts or when spawned
void AOrbiter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AOrbiter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Orbit();
}

void AOrbiter::Orbit()
{
	FVector center;
	if (targetActor)
	{
		center = targetActor->GetActorLocation();
	}
	else
	{
		center = GetActorLocation();
	}

	// Calculate orbit position
	float time = GetWorld()->GetTimeSeconds();
	float angle = time * revolutionSpeed;

	float x = center.X + range * FMath::Cos(angle);
	float y = center.Y + range * FMath::Sin(angle);
	float z = center.Z;                             // Keep aligned with target

	SetActorLocation(FVector(x, y, z));

	// Apply rotation based on rotationSpeed
	FRotator deltaRotation(0.0f, rotationSpeed, 0.0f);
	AddActorWorldRotation(deltaRotation * GetWorld()->GetDeltaSeconds());
}