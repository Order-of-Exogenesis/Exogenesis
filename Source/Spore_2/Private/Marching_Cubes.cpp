

// Marching_Cubes.cpp
#include "Marching_Cubes.h"
#include "Kismet/KismetMathLibrary.h"


void UMarching_Cubes::GenerateMesh(UProceduralMeshComponent* MeshComponent, float Radius, int Resolution)
{
    // ������� ������������� ���� ����������
    MeshComponent->ClearMesh();

    // ��������� ������ ������� ���� � ��������� Marching Cubes
    float cubeSize = Radius / Resolution;

    //������� ��� �������� ������, �������������, �������� � �.�.
    TArray<FVector> Vertices;
    TArray<int32> Triangles;
    TArray<FVector> Normals;
    TArray<FVector2D> UVs;
    TArray<FLinearColor> VertexColors;
    TArray<FProcMeshTangent> Tangents;

    // ����������� �� ������, �������� ����
    for (int x = 0; x < Resolution; ++x)
    {
        for (int y = 0; y < Resolution; ++y)
        {
            for (int z = 0; z < Resolution; ++z)
            {
                // ���������� ������� �������� ����
                FVector position(x * cubeSize, y * cubeSize, z * cubeSize);

                //���������, ��������� �� ������� ��� ������ �����������
                if (DensityFunction(position, Radius) > 0)
                {
                    // ���� ��� ������ �����������, ������� ����������� ��� (��� ���������� ������)
                    int startVertex = Vertices.Num();
                    Vertices.Add(position);
                    Vertices.Add(position + FVector(cubeSize, 0, 0));
                    Vertices.Add(position + FVector(cubeSize, cubeSize, 0));
                    //��������� ��������� ������� ����������� ����

                    // ��������� ������������, ���������� ����� ����
                    Triangles.Add(startVertex);
                    Triangles.Add(startVertex + 1);
                    Triangles.Add(startVertex + 2);
                    //��������� ������ ������������

                }
            }
        }
    }

    // ������� ������ ����, ����� �� ����������� � ����
    MeshComponent->CreateMeshSection(0, Vertices, Triangles, Normals, UVs, VertexColors, Tangents, true);
}

// �������, ������������ ��������� � �����.  � ������ ������, ��� ���.
float UMarching_Cubes::DensityFunction(FVector Point, float Radius)
{
    // ���������� �� ������ ���������
    float distance = Point.Size();
    // ���� ������ ������� - ������ "����"
    return Radius - distance;
}
