// I used a lot of copyrightable things here

// OriginsTable.h
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Origins_Table.h"

// Forward-declare your already existing enumeration
UENUM(BlueprintType)
enum class EOriginStart : uint8;

// Your struct
USTRUCT(BlueprintType)
struct FOrigins
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Origin")
    FText Name;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Origin")
    FText Ability1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Origin")
    FText Ability2;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Origin")
    FText Description;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Origin")
    float Origin_ID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Origin")
    bool bSecondNegative;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Origin")
    EOriginStart Start_Date;
};

// Your data asset (the “table”)
UCLASS(BlueprintType)
class YOURPROJECT_API UOriginsTable : public UPrimaryDataAsset
{
    GENERATED_BODY()

public:
    UOriginsTable();

    // This will act like your "Data Table"
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Origins")
    TArray<FOrigins> OriginsList;
};


