

// Marching_Cubes.cpp
#include "Marching_Cubes.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"


AMarching_Cubes::AMarching_Cubes()
{
	PrimaryActorTick.bCanEverTick = false;


	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;


	// Load the basic Engine sphere mesh
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMesh(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
	if (SphereMesh.Succeeded())
	{
		MeshComponent->SetStaticMesh(SphereMesh.Object);
	}


	// Load default engine material
	static ConstructorHelpers::FObjectFinder<UMaterial> Material(TEXT("/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial"));
	if (Material.Succeeded())
	{
		MeshComponent->SetMaterial(0, Material.Object);
	}
}


void AMarching_Cubes::BeginPlay()
{
	Super::BeginPlay();
	// Sphere will be visible as soon as you drop this actor into the level.
}
