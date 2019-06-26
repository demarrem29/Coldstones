// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ColdStones.h"
#include "GameFramework/PlayerController.h"
#include "Cone.h"
#include "ColdStonesPCBase.generated.h"

/**
 * 
 */
UCLASS()
class COLDSTONES_API AColdStonesPCBase : public APlayerController
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pointers")
		AColdStonesGameModeBase* mygamemode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pointers")
		UPuzzle* mypuzzle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PuzzleProperties")
		struct FCone CurrentGuess;

	UFUNCTION(BlueprintCallable, Category = "PuzzleFunctions")
		void Init();
	
	UFUNCTION(BlueprintCallable, Category = "PuzzleFunctions")
		void ModifyScoop(UPARAM(ref) EFlavors& inScoop, UPARAM(ref) int ScoopIndex);

protected:
	virtual void BeginPlay() override;
};
