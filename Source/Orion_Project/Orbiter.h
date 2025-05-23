#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h" // Added for mesh editing
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	AActor* targetActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	float revolutionSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category  = "Default")
	float rotationSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	float range;
};
