

// Marching_Cubes.cpp
#include "Marching_Cubes.h"
#include "Kismet/KismetMathLibrary.h"


void UMarching_Cubes::GenerateMesh(UProceduralMeshComponent* MeshComponent, float Radius, int Resolution)
{
    // Очистка существующего меша компонента
    MeshComponent->ClearMesh();

    // Вычисляем размер каждого куба в алгоритме Marching Cubes
    float cubeSize = Radius / Resolution;

    //Массивы для хранения вершин, треугольников, нормалей и т.д.
    TArray<FVector> Vertices;
    TArray<int32> Triangles;
    TArray<FVector> Normals;
    TArray<FVector2D> UVs;
    TArray<FLinearColor> VertexColors;
    TArray<FProcMeshTangent> Tangents;

    // Итерируемся по объему, создавая кубы
    for (int x = 0; x < Resolution; ++x)
    {
        for (int y = 0; y < Resolution; ++y)
        {
            for (int z = 0; z < Resolution; ++z)
            {
                // Определяем позицию текущего куба
                FVector position(x * cubeSize, y * cubeSize, z * cubeSize);

                //Проверяем, находится ли текущий куб внутри поверхности
                if (DensityFunction(position, Radius) > 0)
                {
                    // Если куб внутри поверхности, создаем примитивный куб (это упрощенный пример)
                    int startVertex = Vertices.Num();
                    Vertices.Add(position);
                    Vertices.Add(position + FVector(cubeSize, 0, 0));
                    Vertices.Add(position + FVector(cubeSize, cubeSize, 0));
                    //Добавляем остальные вершины упрощенного куба

                    // Добавляем треугольники, образующие грань куба
                    Triangles.Add(startVertex);
                    Triangles.Add(startVertex + 1);
                    Triangles.Add(startVertex + 2);
                    //Добавляем другие треугольники

                }
            }
        }
    }

    // Создаем секцию меша, чтобы он отобразился в игре
    MeshComponent->CreateMeshSection(0, Vertices, Triangles, Normals, UVs, VertexColors, Tangents, true);
}

// Функция, определяющая плотность в точке.  В данном случае, это шар.
float UMarching_Cubes::DensityFunction(FVector Point, float Radius)
{
    // Расстояние от начала координат
    float distance = Point.Size();
    // Если меньше радиуса - внутри "шара"
    return Radius - distance;
}
