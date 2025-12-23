#include "ACreatureBody.h"

// Set a unique material for the generated mesh
#define MESH_MATERIAL_PATH TEXT("Material'/Game/Materials/M_CreatureBase.M_CreatureBase'") 
// NOTE: You must create a basic Material (M_CreatureBase) in your Content Browser 
// at this path for the material assignment to work.

ACreatureBody::ACreatureBody()
{
    // Set this actor to call Tick() every frame. 
    PrimaryActorTick.bCanEverTick = true;

    // Create the procedural mesh component
    MeshComponent = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("GeneratedMesh"));
    RootComponent = MeshComponent;
}

void ACreatureBody::BeginPlay()
{
    Super::BeginPlay();

    // Generate the initial mesh when the actor is spawned
    RegenerateBodyMesh(Radius, Height);
}

void ACreatureBody::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    // Future procedural animation logic can go here (e.g., breathing, idle wobbling)
}

void ACreatureBody::RegenerateBodyMesh(float NewRadius, float NewHeight)
{
    Radius = NewRadius;
    Height = NewHeight;

    TArray<FVector> Vertices;
    TArray<int32> Triangles;
    TArray<FVector> Normals;
    TArray<FVector2D> UV0;
    // TArray<FProcMeshTangent> Tangents; // Omitted for simplicity

    GenerateCapsuleMesh(Vertices, Triangles, Normals, UV0);

    // Clear previous sections
    MeshComponent->ClearAllMeshSections();

    // Create a mesh section from the generated data
    MeshComponent->CreateMeshSection_LinearColor(
        0, // Section Index
        Vertices,
        Triangles,
        Normals,
        UV0,
        TArray<FLinearColor>(), // Vertex Colors (empty for now)
        TArray<FProcMeshTangent>(), // Tangents (empty for now)
        false // Collision
    );

    // Load and set the material
    static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialAsset(MESH_MATERIAL_PATH);
    if (MaterialAsset.Succeeded())
    {
        MeshComponent->SetMaterial(0, MaterialAsset.Object);
    }
}

// *** CRITICAL GEOMETRY CALCULATION ***
void ACreatureBody::GenerateCapsuleMesh(TArray<FVector>& Vertices, TArray<int32>& Triangles, TArray<FVector>& Normals, TArray<FVector2D>& UV0)
{
    // The half-height of the cylindrical part
    const float HalfCylinderHeight = Height * 0.5f;

    // --- 1. Generate the main cylinder body ---
    for (int h = 0; h <= HeightSegments; h++)
    {
        float V = (float)h / HeightSegments;
        float Z = -HalfCylinderHeight + 2 * HalfCylinderHeight * V;

        for (int i = 0; i <= Sides; i++)
        {
            float Angle = (float)i / Sides * 2.0f * PI;
            float X = FMath::Cos(Angle) * Radius;
            float Y = FMath::Sin(Angle) * Radius;

            Vertices.Add(FVector(X, Y, Z));
            Normals.Add(FVector(X, Y, 0.0f).GetSafeNormal()); // Simple normal approximation
            UV0.Add(FVector2D((float)i / Sides, V));

            // Create triangles for the quad between this vertex and the previous row/segment
            if (h < HeightSegments && i < Sides)
            {
                int32 Current = h * (Sides + 1) + i;
                int32 Next = Current + 1;
                int32 RowAbove = (h + 1) * (Sides + 1) + i;
                int32 NextRowAbove = RowAbove + 1;

                // Triangle 1 (Bottom-left to Top-right)
                Triangles.Add(Current);
                Triangles.Add(NextRowAbove);
                Triangles.Add(RowAbove);

                // Triangle 2 (Bottom-right to Top-right)
                Triangles.Add(Current);
                Triangles.Add(Next);
                Triangles.Add(NextRowAbove);
            }
        }
    }

    //
    // --- 2. Simplified Spherical Caps (Top and Bottom) ---
    // A true capsule has spherical caps. For simplicity, we can cap the cylinder with simple discs,
    // or add a very simple sphere generation routine for the ends.
    // For a full Spore-like editor, you'd integrate the cylinder and two half-spheres smoothly.
    // Let's stick to the simplest deformable object for now: the cylinder, as it's the core. 
    // The distortion logic is what matters most.
}

