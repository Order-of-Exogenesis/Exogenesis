#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "ACreatureBody.generated.h"

UCLASS()
class CREATUREEDITORPROJECT_API ACreatureBody : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ACreatureBody();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Component to generate the mesh data
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
    UProceduralMeshComponent* MeshComponent;

    // --- Core Generation Parameters ---

    UPROPERTY(EditAnywhere, Category = "Generation")
    float Radius = 50.0f;

    UPROPERTY(EditAnywhere, Category = "Generation")
    float Height = 100.0f; // Height of the cylindrical part

    UPROPERTY(EditAnywhere, Category = "Generation")
    int32 Sides = 16; // Number of subdivisions around the circumference

    UPROPERTY(EditAnywhere, Category = "Generation")
    int32 HeightSegments = 10; // Number of subdivisions along the height

    // --- Public Deformation Function (The key to your editor) ---

    // Function to regenerate the mesh with new parameters
    UFUNCTION(BlueprintCallable, Category = "CreatureEditor")
    void RegenerateBodyMesh(float NewRadius, float NewHeight);

private:
    // Core function to generate the mesh data (vertices, triangles, etc.)
    void GenerateCapsuleMesh(TArray<FVector>& Vertices, TArray<int32>& Triangles, TArray<FVector>& Normals, TArray<FVector2D>& UV0);
};
