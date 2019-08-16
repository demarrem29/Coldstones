// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "ColdStones.h"
#include "Components/ActorComponent.h"
#include "Puzzle.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnGuessDelegate, bool, gameover, int, attempts, int, locks_opened);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COLDSTONES_API UPuzzle : public UActorComponent
{
	GENERATED_BODY()
public:	
	// Declare default values for this component's properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PuzzleProperties")
		int attempts;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PuzzleProperties")
		int locks_opened;
	UPROPERTY(VisibleAnywhere)
		class AColdStonesGameModeBase* mymode;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PuzzleProperties")
		TArray<FCone> Cones;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PuzzleProperties")
		int numconescorrect;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PuzzleProperties")
		int numflavorscorrect;
	UPROPERTY(BlueprintAssignable, Category = "Delegates")
		FOnGuessDelegate OnGuess;

	void init();
	UFUNCTION(BlueprintCallable, Category="PuzzleFunctions")
		void guess(UPARAM(ref) struct FCone& inCone);
	UPuzzle();

	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;	
};
