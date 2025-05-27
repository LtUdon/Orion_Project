#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h" // Added for mesh editing
#include "Affiliation.h" // Include the Affiliation enum header
#include "Orbiter.generated.h"

UCLASS()
class ORION_PROJECT_API AOrbiter : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOrbiter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Orbit();

	// Editable mesh component
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Default")
	UStaticMeshComponent* mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default", Meta = (ToolTip = "Choose an actor for this object to orbit around."))
	AActor* targetActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default", Meta = (ToolTip = "Speed for this object revolve around the Target Actor. (Scaled by 0.01)."))
	float revolutionSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category  = "Default", Meta = (ToolTip = "Speed for this object revolve around the Target Actor."))
	float rotationSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default", Meta = (ToolTip = "Distance for this object to revolve around the Target Actor."))
	float range;

	UPROPERTY(editAnywhere, BlueprintReadWrite, Category = "Default", Meta = (ToolTip = "Determines this object is capturable by any team."))
	bool isCapturable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default", Meta = (ToolTip = "Object affilication."))
	EAffiliation affiliation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default", Meta = (ToolTip = "Maximum amount of ships for any team to have for this object."))
	int maxShipCount;

	UPROPERTY(Transient)
	float initialAngle = 0.0f; // In RAD
};
