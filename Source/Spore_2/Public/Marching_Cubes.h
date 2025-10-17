// I used a lot of copyrightable things here

#pragma once

#include "MarchingCubes.generated.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"

UCLASS()
class YOURPROJECT_API AMarchingCubes : public AActor
{
    GENERATED_BODY()

public:
    AMarchingCubes();

    // Build mesh in editor and at runtime
    virtual void OnConstruction(const FTransform& Transform) override;
    virtual void BeginPlay() override;

    // Call to rebuild from Blueprint/Editor
    UFUNCTION(CallInEditor, BlueprintCallable, Category = "MarchingCubes")
    void RebuildMesh();

protected:
    // Procedural mesh component
    UPROPERTY(VisibleAnywhere, Category = "MarchingCubes")
    UProceduralMeshComponent* ProcMesh;

    // Grid / domain parameters
    UPROPERTY(EditAnywhere, Category = "MarchingCubes", meta = (ClampMin = "4", UIMin = "4"))
    int32 GridSizeX = 32;

    UPROPERTY(EditAnywhere, Category = "MarchingCubes", meta = (ClampMin = "4", UIMin = "4"))
    int32 GridSizeY = 32;

    UPROPERTY(EditAnywhere, Category = "MarchingCubes", meta = (ClampMin = "4", UIMin = "4"))
    int32 GridSizeZ = 32;

    // Size of each voxel cell (world units)
    UPROPERTY(EditAnywhere, Category = "MarchingCubes", meta = (ClampMin = "0.1"))
    float CellSize = 10.0f;

    // iso threshold (0 works with our density formulation)
    UPROPERTY(EditAnywhere, Category = "MarchingCubes")
    float IsoLevel = 0.0f;

    // Default metaball radius (if influence actor doesn't provide its own)
    UPROPERTY(EditAnywhere, Category = "MarchingCubes", meta = (ClampMin = "0.1"))
    float MetaballRadius = 40.0f;

    // Influence actors (assign bone-handle actors or Spheres). Their world positions are used as metaball centers.
    UPROPERTY(EditInstanceOnly, EditAnywhere, Category = "MarchingCubes")
    TArray<AActor*> InfluenceActors;

private:
    // density field storage (size = GridSizeX * GridSizeY * GridSizeZ)
    TArray<float> DensityField;

    // Build density field from InfluenceActors
    void BuildDensityField();

    // Convert (x,y,z) into linear index for DensityField
    FORCEINLINE int32 DensityIndex(int32 X, int32 Y, int32 Z) const
    {
        return X + GridSizeX * (Y + GridSizeY * Z);
    }

    // Polygonize density field with marching cubes -> create mesh section
    void Polygonize();

    // Interpolate vertex along edge
    FVector VertexInterp(float iso, const FVector& p1, const FVector& p2, float valp1, float valp2) const;

    // Tables (edgeTable & triTable) used by marching cubes
    static const int edgeTable[256];
    static const int triTable[256][16];
};






