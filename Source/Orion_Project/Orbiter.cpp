// Fill out your copyright notice in the Description page of Project Settings.


#include "Orbiter.h"

// Sets default values
AOrbiter::AOrbiter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	// Create mesh and set as root
	OrbiterMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OrbiterMesh"));
	RootComponent = OrbiterMesh;

	// Default values
	revolutionSpeed	= 1.0f;
	rotationSpeed	= 30.0f;
	orbitRadius		= 100.0f;
	faction         = EAffiliation::None;
}

// Called when the game starts or when spawned
void AOrbiter::BeginPlay()
{
	Super::BeginPlay();
	
	FVector center    = IsValid(targetActor) ? targetActor->GetActorLocation() : GetActorLocation();
	FVector toOrbiter = GetActorLocation() - center;
	initialAngle      = FMath::Atan2(toOrbiter.Y, toOrbiter.X); // Calculate initial angle based on the current position
	
	loggedLocation = GetActorLocation();
}

// Called every frame
void AOrbiter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Orbit();

	loggedLocation = GetActorLocation();
}

// Handles orbit behavior
void AOrbiter::Orbit()
{	
	float scalar                = 0.01f; // Scale factor for revolution speed
	float scaledRevolutionSpeed = revolutionSpeed * scalar;
	FVector center;
	center = targetActor ? targetActor->GetActorLocation() : GetActorLocation();

	// Calculate orbit position
	float time = GetWorld()->GetTimeSeconds();
	float angle = time * scaledRevolutionSpeed + initialAngle;

	float x = center.X + orbitRadius * FMath::Cos(angle);
	float y = center.Y + orbitRadius * FMath::Sin(angle);
	float z = center.Z;                             // Keep aligned with target

	SetActorLocation(FVector(x, y, z));

	// Apply rotation based on rotationSpeed
	FRotator deltaRotation(0.0f, rotationSpeed, 0.0f);
	AddActorWorldRotation(deltaRotation * GetWorld()->GetDeltaSeconds());
}