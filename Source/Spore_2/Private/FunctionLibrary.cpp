#include "PlanetNoiseLibrary.h"

float UPlanetNoiseLibrary::Perlin3D(FVector Position)
{
    return FMath::PerlinNoise3D(Position);
}