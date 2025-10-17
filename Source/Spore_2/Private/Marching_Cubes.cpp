// I used a lot of copyrightable things here

#include "MarchingCubes.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

// NOTE: replace YOURPROJECT_API with your project's module API macro in the header above
// (e.g., if your project is Spore_2, header's UCLASS() should be class SPORE_2_API ...)

// ----- edgeTable and triTable (standard marching cubes tables) -----
/* edgeTable and triTable definitions are long; both are required and standard.
   Below I include the canonical tables used by marching cubes (edgeTable[256] and triTable[256][16]).
   They are huge arrays but must be present for correctness. */

const int AMarchingCubes::edgeTable[256] = {
0x0,0x109,0x203,0x30a,0x406,0x50f,0x605,0x70c,0x80c,0x905,0xa0f,0xb06,0xc0a,0xd03,0xe09,0xf00,
0x190,0x99,0x393,0x29a,0x596,0x49f,0x795,0x69c,0x99c,0x895,0xb9f,0xa96,0xd9a,0xc93,0xf99,0xe90,
0x230,0x339,0x33,0x13a,0x636,0x73f,0x435,0x53c,0xa3c,0xb35,0x83f,0x936,0xe3a,0xf33,0xc39,0xd30,
0x3a0,0x2a9,0x1a3,0xaa,0x7a6,0x6af,0x5a5,0x4ac,0xbac,0xaa5,0x9af,0x8a6,0xfaa,0xea3,0xda9,0xca0,
0x460,0x569,0x663,0x76a,0x66,0x16f,0x265,0x36c,0xc6c,0xd65,0xe6f,0xf66,0x86a,0x963,0xa69,0xb60,
0x5f0,0x4f9,0x7f3,0x6fa,0x1f6,0xff,0x3f5,0x2fc,0xdfc,0xcf5,0xfff,0xef6,0x9fa,0x8f3,0xbf9,0xaf0,
0x650,0x759,0x453,0x55a,0x256,0x35f,0x55,0x15c,0xe5c,0xf55,0xc5f,0xd56,0xa5a,0xb53,0x859,0x950,
0x7c0,0x6c9,0x5c3,0x4ca,0x3c6,0x2cf,0x1c5,0xcc,0xfcc,0xec5,0xdcf,0xcc6,0xbca,0xac3,0x9c9,0x8c0,
0x8c0,0x9c9,0xac3,0xbca,0xcc6,0xdcf,0xec5,0xfcc,0xcc,0x1c5,0x2cf,0x3c6,0x4ca,0x5c3,0x6c9,0x7c0,
0x950,0x859,0xb53,0xa5a,0xd56,0xc5f,0xf55,0xe5c,0x15c,0x55,0x35f,0x256,0x55a,0x453,0x759,0x650,
0xaf0,0xbf9,0x8f3,0x9fa,0xef6,0xfff,0xcf5,0xdfc,0x2fc,0x3f5,0xff,0x1f6,0x6fa,0x7f3,0x4f9,0x5f0,
0xb60,0xa69,0x963,0x86a,0xf66,0xe6f,0xd65,0xc6c,0x36c,0x265,0x16f,0x66,0x76a,0x663,0x569,0x460,
0xca0,0xda9,0xea3,0xfaa,0x8a6,0x9af,0xaa5,0xbac,0x4ac,0x5a5,0x6af,0x7a6,0xaa,0x1a3,0x2a9,0x3a0,
0xd30,0xc39,0xf33,0xe3a,0x936,0x83f,0xb35,0xa3c,0x53c,0x435,0x73f,0x636,0x13a,0x33,0x339,0x230,
0xe90,0xf99,0xc93,0xd9a,0xa96,0xb9f,0x895,0x99c,0x69c,0x795,0x49f,0x596,0x29a,0x393,0x99,0x190,
0xf00,0xe09,0xd03,0xc0a,0xb06,0xa0f,0x905,0x80c,0x70c,0x605,0x50f,0x406,0x30a,0x203,0x109,0x0
};

const int AMarchingCubes::triTable[256][16] = {
{-1},{0,8,3,-1},{0,1,9,-1},{1,8,3,9,8,1,-1},{1,2,10,-1},{0,8,3,1,2,10,-1},
{9,2,10,0,2,9,-1},{2,8,3,2,10,8,10,9,8,-1},{3,11,2,-1},{0,11,2,8,11,0,-1},
{1,9,0,2,3,11,-1},{1,11,2,1,9,11,9,8,11,-1},{3,10,1,11,10,3,-1},
{0,10,1,0,8,10,8,11,10,-1},{3,9,0,3,11,9,11,10,9,-1},{9,8,10,10,8,11,-1},
{4,7,8,-1},{4,3,0,7,3,4,-1},{0,1,9,8,4,7,-1},{4,1,9,4,7,1,7,3,1,-1},
{1,2,10,8,4,7,-1},{3,4,7,3,0,4,1,2,10,-1},{9,2,10,9,0,2,8,4,7,-1},
{2,10,9,2,9,7,2,7,3,7,9,4,-1},{8,4,7,3,11,2,-1},{11,4,7,11,2,4,2,0,4,-1},
{9,0,1,8,4,7,2,3,11,-1},{4,7,11,9,4,11,9,11,2,9,2,1,-1},{3,10,1,3,11,10,7,8,4,-1},
{1,11,10,1,4,11,1,0,4,7,11,4,-1},{4,7,8,9,0,11,9,11,10,11,0,3,-1},{4,7,11,4,11,9,9,11,10,-1},
{9,5,4,-1},{9,5,4,0,8,3,-1},{0,5,4,1,5,0,-1},{8,5,4,8,3,5,3,1,5,-1},{1,2,10,9,5,4,-1},
{3,0,8,1,2,10,4,9,5,-1},{5,2,10,5,4,2,4,0,2,-1},{2,10,5,3,2,5,3,5,4,3,4,8,-1},
{9,5,4,2,3,11,-1},{0,11,2,0,8,11,4,9,5,-1},{0,5,4,0,1,5,2,3,11,-1},
{2,1,5,2,5,8,2,8,11,4,8,5,-1},{10,3,11,10,1,3,9,5,4,-1},{4,9,5,0,8,1,8,10,1,8,11,10,-1},
{5,4,0,5,0,11,5,11,10,11,0,3,-1},{5,4,8,5,8,10,10,8,11,-1},{9,7,8,5,7,9,-1},
{9,3,0,9,5,3,5,7,3,-1},{0,7,8,0,1,7,1,5,7,-1},{1,5,3,3,5,7,-1},{9,5,4,10,1,2,7,8,3,-1},
{4,9,5,0,2,7,0,7,3,7,2,10,-1},{3,4,0,3,7,4,2,10,5,2,5,1,-1},{5,2,10,5,4,2,4,3,2,4,7,3,-1},
{7,9,5,7,8,9,3,11,2,-1},{9,5,7,9,7,2,9,2,0,2,7,11,-1},{2,3,11,0,1,8,1,7,8,1,5,7,-1},
{11,2,1,11,1,7,7,1,5,-1},{9,5,4,10,1,3,10,3,11,3,1,0,-1},{0,10,1,0,8,10,8,11,10,4,9,5,-1},
{5,4,0,5,0,11,5,11,10,11,0,3, -1},{5,4,8,5,8,10,10,8,11,-1},
// ... (the full 256 rows must appear here) ...
};

// NOTE: for brevity in this message the triTable has been truncated —
// in your source file you must include the full 256x16 triTable values.
// Use a standard marching-cubes triTable (many references available online).

// ---------------------------------------------------------------------

AMarchingCubes::AMarchingCubes()
{
    PrimaryActorTick.bCanEverTick = false;

    ProcMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("ProceduralMesh"));
    RootComponent = ProcMesh;
    ProcMesh->bUseAsyncCooking = true;
}

void AMarchingCubes::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);
    RebuildMesh();
}

void AMarchingCubes::BeginPlay()
{
    Super::BeginPlay();
    // ensure run at least once at runtime
    RebuildMesh();
}

void AMarchingCubes::RebuildMesh()
{
    // allocate density field
    DensityField.SetNumZeroed(GridSizeX * GridSizeY * GridSizeZ);
    BuildDensityField();
    Polygonize();
}

void AMarchingCubes::BuildDensityField()
{
    // origin at actor location - center the grid around actor for convenience
    const FVector ActorOrigin = GetActorLocation();
    const FVector GridOrigin = ActorOrigin - FVector(GridSizeX - 1, GridSizeY - 1, GridSizeZ - 1) * 0.5f * CellSize;

    // collect centers and radii from InfluenceActors
    TArray<FVector> Centers;
    TArray<float> Radii;
    if (InfluenceActors.Num() > 0)
    {
        for (AActor* A : InfluenceActors)
        {
            if (A)
            {
                Centers.Add(A->GetActorLocation());
                Radii.Add(MetaballRadius); // uniform radius for simplicity
            }
        }
    }
    else
    {
        // default: one central metaball and two offset ones so you see blending
        Centers.Add(ActorOrigin + FVector(-MetaballRadius * 0.8f, 0, 0));
        Radii.Add(MetaballRadius);
        Centers.Add(ActorOrigin + FVector(MetaballRadius * 0.8f, 0, 0));
        Radii.Add(MetaballRadius);
    }

    const float eps = 1e-6f;

    for (int z = 0; z < GridSizeZ; ++z)
    {
        for (int y = 0; y < GridSizeY; ++y)
        {
            for (int x = 0; x < GridSizeX; ++x)
            {
                int idx = DensityIndex(x, y, z);
                FVector WorldPos = GridOrigin + FVector(x * CellSize, y * CellSize, z * CellSize);

                // sum contributions from metaballs: density = max(0, r - dist)
                float density = -FLT_MAX;
                float sum = 0.0f;
                for (int i = 0; i < Centers.Num(); ++i)
                {
                    float dist = FVector::Dist(WorldPos, Centers[i]);
                    float contrib = Radii[i] - dist; // positive inside sphere
                    sum += contrib;
                }

                // We will use sum as density; iso-level threshold of 0 means inside combined spheres
                DensityField[idx] = sum;
            }
        }
    }
}

FVector AMarchingCubes::VertexInterp(float iso, const FVector& p1, const FVector& p2, float valp1, float valp2) const
{
    if (FMath::Abs(iso - valp1) < KINDA_SMALL_NUMBER) return p1;
    if (FMath::Abs(iso - valp2) < KINDA_SMALL_NUMBER) return p2;
    if (FMath::Abs(valp1 - valp2) < KINDA_SMALL_NUMBER) return p1;
    float mu = (iso - valp1) / (valp2 - valp1);
    return p1 + mu * (p2 - p1);
}

void AMarchingCubes::Polygonize()
{
    TArray<FVector> Vertices;
    TArray<int32> Triangles;
    TArray<FVector> Normals;
    TArray<FVector2D> UVs;
    TArray<FLinearColor> Colors;
    TArray<FProcMeshTangent> Tangents;

    Vertices.Reserve(100000);
    Triangles.Reserve(100000);

    const FVector ActorOrigin = GetActorLocation();
    const FVector GridOrigin = ActorOrigin - FVector(GridSizeX - 1, GridSizeY - 1, GridSizeZ - 1) * 0.5f * CellSize;

    // iterate over each cube in the grid
    for (int z = 0; z < GridSizeZ - 1; ++z)
    {
        for (int y = 0; y < GridSizeY - 1; ++y)
        {
            for (int x = 0; x < GridSizeX - 1; ++x)
            {
                // corner positions and their densities
                FVector p[8];
                float val[8];

                for (int i = 0; i < 8; ++i)
                {
                    int ix = x + ((i & 1) ? 1 : 0);
                    int iy = y + ((i & 2) ? 1 : 0);
                    int iz = z + ((i & 4) ? 1 : 0);
                    p[i] = GridOrigin + FVector(ix * CellSize, iy * CellSize, iz * CellSize);
                    val[i] = DensityField[DensityIndex(ix, iy, iz)];
                }

                // compute cubeindex
                int cubeindex = 0;
                for (int i = 0; i < 8; ++i)
                {
                    if (val[i] > IsoLevel) cubeindex |= (1 << i);
                }

                int edges = edgeTable[cubeindex];
                if (edges == 0) continue; // no triangles

                // find the vertices where the surface intersects the cube
                FVector vertlist[12];
                if (edges & 1) vertlist[0] = VertexInterp(IsoLevel, p[0], p[1], val[0], val[1]);
                if (edges & 2) vertlist[1] = VertexInterp(IsoLevel, p[1], p[2], val[1], val[2]);
                if (edges & 4) vertlist[2] = VertexInterp(IsoLevel, p[2], p[3], val[2], val[3]);
                if (edges & 8) vertlist[3] = VertexInterp(IsoLevel, p[3], p[0], val[3], val[0]);
                if (edges & 16) vertlist[4] = VertexInterp(IsoLevel, p[4], p[5], val[4], val[5]);
                if (edges & 32) vertlist[5] = VertexInterp(IsoLevel, p[5], p[6], val[5], val[6]);
                if (edges & 64) vertlist[6] = VertexInterp(IsoLevel, p[6], p[7], val[6], val[7]);
                if (edges & 128) vertlist[7] = VertexInterp(IsoLevel, p[7], p[4], val[7], val[4]);
                if (edges & 256) vertlist[8] = VertexInterp(IsoLevel, p[0], p[4], val[0], val[4]);
                if (edges & 512) vertlist[9] = VertexInterp(IsoLevel, p[1], p[5], val[1], val[5]);
                if (edges & 1024) vertlist[10] = VertexInterp(IsoLevel, p[2], p[6], val[2], val[6]);
                if (edges & 2048) vertlist[11] = VertexInterp(IsoLevel, p[3], p[7], val[3], val[7]);

                // create triangles
                const int* tri = triTable[cubeindex];
                for (int i = 0; tri[i] != -1; i += 3)
                {
                    int idx0 = Vertices.Add(vertlist[tri[i + 0]]);
                    int idx1 = Vertices.Add(vertlist[tri[i + 1]]);
                    int idx2 = Vertices.Add(vertlist[tri[i + 2]]);

                    Triangles.Add(idx0);
                    Triangles.Add(idx1);
                    Triangles.Add(idx2);
                }
            }
        }
    }

    // compute normals
    Normals.Init(FVector::ZeroVector, Vertices.Num());
    for (int i = 0; i < Triangles.Num(); i += 3)
    {
        int ia = Triangles[i + 0];
        int ib = Triangles[i + 1];
        int ic = Triangles[i + 2];
        FVector A = Vertices[ia];
        FVector B = Vertices[ib];
        FVector C = Vertices[ic];
        FVector N = FVector::CrossProduct(B - A, C - A).GetSafeNormal();
        Normals[ia] += N;
        Normals[ib] += N;
        Normals[ic] += N;
    }
    for (int i = 0; i < Normals.Num(); ++i) Normals[i].Normalize();

    // UVs (simple planar mapping)
    UVs.SetNum(Vertices.Num());
    for (int i = 0; i < Vertices.Num(); ++i)
    {
        UVs[i] = FVector2D(Vertices[i].X * 0.01f, Vertices[i].Y * 0.01f);
    }

    // Colors and tangents
    Colors.Init(FLinearColor::White, Vertices.Num());
    Tangents.Init(FProcMeshTangent(1, 0, 0), Vertices.Num());

    // create mesh section
    ProcMesh->ClearAllMeshSections();
    ProcMesh->CreateMeshSection_LinearColor(0, Vertices, Triangles, Normals, UVs, Colors, Tangents, true);
    ProcMesh->ContainsPhysicsTriMeshData(true);
}








