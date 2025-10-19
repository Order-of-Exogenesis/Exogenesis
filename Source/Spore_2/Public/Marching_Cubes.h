// Marching_Cubes.h
#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Marching_Cubes.generated.h"


UCLASS()
class SPORE_2_API AMarching_Cubes : public AActor
{
	GENERATED_BODY()


public:
	AMarching_Cubes();


protected:
	virtual void BeginPlay() override;


private:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComponent;
};













