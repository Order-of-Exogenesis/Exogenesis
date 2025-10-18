
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Marching_Cubes.generated.h"

UCLASS()
class SPORE_2_API AMarching_Cubes : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor
    AMarching_Cubes();

    // BeginPlay function (public, safe)
    virtual void BeginPlay() override;

private:
    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* SphereMesh;
};












