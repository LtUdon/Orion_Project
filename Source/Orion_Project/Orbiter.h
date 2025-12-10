#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h" // Added for mesh editing
#include "Orbiter.generated.h"

UCLASS()
class ORION_PROJECT_API AOrbiter : public AActor
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	// Sets default values for this actor's properties
	AOrbiter();

	void Orbit();

	// Editable mesh component
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Orbiter")
	UStaticMeshComponent* OrbiterMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Orbiter", Meta = (ToolTip = "Choose an actor for this object to orbit around."))
	AActor* targetActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Orbiter", Meta = (ToolTip = "Speed for this object revolve around the Target Actor. (Scaled by 0.01)."))
	float revolutionSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category  = "Orbiter", Meta = (ToolTip = "Speed for this object revolve around the Target Actor."))
	float rotationSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Orbiter", Meta = (ToolTip = "Distance for this object to revolve around the Target Actor."))
	float range;

	UPROPERTY(Transient)
	float initialAngle = 0.0f; // In RAD
};
