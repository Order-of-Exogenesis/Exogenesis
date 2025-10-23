// Marching_Cubes.h
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ProceduralMeshComponent.h"
#include "Marching_Cubes.generated.h"

UCLASS()
class SPORE_2_API UMarching_Cubes : public UObject
{
    GENERATED_BODY()

public:
    // Функция для создания меша Marching Cubes
    UFUNCTION(BlueprintCallable, Category = "MarchingCubes")
    void GenerateMesh(UProceduralMeshComponent* MeshComponent, float Radius, int Resolution);

private:
    // Функция для вычисления значения плотности в точке
    float DensityFunction(FVector Point, float Radius);
};












