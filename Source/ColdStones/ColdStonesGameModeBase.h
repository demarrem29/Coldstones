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
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameoverDelegate, bool, gameover);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWinDelegate, bool, win);

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

	UFUNCTION(BlueprintImplementableEvent, Category = GameEvents, meta = (DisplayName = "Game Events"))
		void BP_OnGameover(bool ingameover);

	UFUNCTION(BlueprintImplementableEvent, Category = GameEvents, meta = (DisplayName = "Game Events"))
		void BP_OnWin(bool inwin);

	FOnGameoverDelegate OnGameover;
	FOnWinDelegate OnWin;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
};
