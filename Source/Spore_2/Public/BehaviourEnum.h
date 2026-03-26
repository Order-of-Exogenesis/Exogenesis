

#pragma once

#include "CoreMinimal.h"
#include "BehaviourEnum.generated.h"

UENUM(BlueprintType)
enum class EBehaviourEnum : uint8
{
	Aggressive		UMETA(DisplayName="Aggressive"),
	Peaceful		UMETA(DisplayName ="Peaceful"),
	Adaptive		UMETA(DisplayName = "Adaptive")
};
