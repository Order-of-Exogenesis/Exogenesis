#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "PlanetNoiseLibrary.generated.h"

UCLASS()
class YOURPROJECT_API UPlanetNoiseLibrary
    : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintPure, Category = "Planet|Noise")
    static float Perlin3D(FVector Position);
};