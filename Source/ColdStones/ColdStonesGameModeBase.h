// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "GameFramework/GameModeBase.h"
#include "ColdStones.h"
#include "ColdStonesGameModeBase.generated.h"

/**
 * 
 */

UCLASS()
class COLDSTONES_API AColdStonesGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PuzzleProperties)
		int numstonesperlock;
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PuzzleProperties)
		int numlocks;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PuzzleProperties)
		int numattempts;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PuzzleProperties)
		int numstonecolors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PuzzleProperties)
		int attempts;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PuzzleProperties)
		bool gameover;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PuzzleProperties)
		bool win;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PuzzleProperties)
		bool initialized;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = PuzzleProperties)
		class UPuzzle* mypuzzle;	
	
	UFUNCTION(BlueprintImplementableEvent, Category = GameEvents, meta = (DisplayName = "On Gameover"))
		void BP_OnGameover(bool ingameover);
	UFUNCTION(BlueprintImplementableEvent, Category = GameEvents, meta = (DisplayName = "On Gameover"))
		void BP_OnAttempt(int inattempts);
	UFUNCTION(BlueprintImplementableEvent, Category = GameEvents, meta = (DisplayName = "On Gameover"))
		void BP_OnOpen(int correctguesses);

protected:
	// Called when the game starts
	AColdStonesGameModeBase();
	virtual void BeginPlay() override;
};
