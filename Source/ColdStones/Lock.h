// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <vector>
#include "Lock.generated.h"

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class EColors : uint8
{
	Red 	UMETA(DisplayName = "Red"),
	Orange 	UMETA(DisplayName = "Orange"),
	Yellow	UMETA(DisplayName = "Yellow"),
	Green	UMETA(DisplayName = "Green"),
	Blue	UMETA(DisplayName = "Blue")
};

USTRUCT(BlueprintType)
struct FStone
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enum)
	EColors color;
};

USTRUCT(BlueprintType)
struct FLock
{
	GENERATED_BODY()
	FStone* stones;
};
