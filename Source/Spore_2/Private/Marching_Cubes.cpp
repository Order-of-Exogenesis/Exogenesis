// I used a lot of copyrightable things here
#include "Marching_Cubes.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

AMarching_Cubes::AMarching_Cubes()
{
    PrimaryActorTick.bCanEverTick = false;

    // Initial Thing
    SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SphereMesh"));
    RootComponent = SphereMesh;

    // Load
    static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereAsset(TEXT("/Game/YourFolder/Material_Sphere.Material_Sphere"));
    if (SphereAsset.Succeeded())
    {
        SphereMesh->SetStaticMesh(SphereAsset.Object);
        SphereMesh->SetWorldScale3D(FVector(3.f));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("So sphere for u"));
    }

    SphereMesh->SetVisibility(true);
    SphereMesh->SetMobility(EComponentMobility::Movable);
}

void AMarching_Cubes::BeginPlay()
{
    Super::BeginPlay();

    UE_LOG(LogTemp, Warning, TEXT("Beignplay"));

    // force mesh location
    if (SphereMesh)
    {
        SphereMesh->SetWorldLocation(GetActorLocation());
    }
}














