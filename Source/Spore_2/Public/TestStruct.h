#pragma once

#include "CoreMinimal.h"
#include "TestStruct.generated.h"

USTRUCT(BlueprintType)
struct FTestStruct
{
	GENERATED_BODY()

	UPROPERTY(EditDeaultsOnly, BlueprintReadyOnly)
	FText name;

	UPROPERTY(EditDeaultsOnly, BlueprintReadyOnly)
	float damage;
};
