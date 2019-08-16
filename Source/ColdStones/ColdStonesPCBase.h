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
		AColdStonesGameModeBase* mygamemode;								// Object Reference to Game Mode

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pointers")
		UPuzzle* mypuzzle;													// Object Reference to Puzzle

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PuzzleProperties")
		struct FCone CurrentGuess;											// Ice Cream Cone that we are currently working on
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PuzzleProperties")
		TArray<FCone> BadGuesses;											// Record of cones that we attempted that were not correct

	UFUNCTION(BlueprintCallable, Category = "PuzzleFunctions")
		void Init();														// Allocate memory for variables, setup random starting guess
	
	UFUNCTION(BlueprintCallable, Category = "PuzzleFunctions")
		void ModifyScoop(UPARAM(ref) EFlavors& inScoop, UPARAM(ref) int ScoopIndex);	// When CurrentGuess scoops are clicked by user, update variable to match

	UFUNCTION(Category = "PuzzleFunctions")
		void ModifyGuessScoop(UPARAM(ref)  bool gameover, int attempts, int locks_opened);					// When CurrentGuess scoops are clicked by user, update variable to match
	UFUNCTION(BlueprintImplementableEvent, Category = "PuzzleFunctions")
		void BP_OnGuess(bool gameover, int attempts, int locks_opened);												// Expose delegate to blueprints so we can update UI

protected:
	virtual void BeginPlay() override;
};
