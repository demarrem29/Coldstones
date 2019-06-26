// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Cone.generated.h"

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class EFlavors : uint8
{
	Vanilla 	UMETA(DisplayName = "Vanilla"),
	Chocolate 	UMETA(DisplayName = "Chocolate"),
	Strawberry	UMETA(DisplayName = "Strawberry"),
	MintCC		UMETA(DisplayName = "MintCC"),
	CNC			UMETA(DisplayName = "CNC")
};

USTRUCT(BlueprintType)
struct FCone
{
	GENERATED_BODY()
		
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enum")
		TArray<EFlavors> Scoops;
};