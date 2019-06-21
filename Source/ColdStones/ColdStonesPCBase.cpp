// Fill out your copyright notice in the Description page of Project Settings.


#include "ColdStonesPCBase.h"

void AColdStonesPCBase::AddStone(UPARAM(ref) struct FStone& inStone)
{
	if (!mypuzzle) return;											// Make sure a puzzle has been loaded
	int32 retval;
	CurrentGuess.Stones.Emplace(inStone);							// Append array with passed in stone, construct if necessary
	if (CurrentGuess.Stones.Num() >= mygamemode->numstonesperlock)	// Is the guess complete?
	{
		retval = mypuzzle->guess(CurrentGuess);						// Send the guess to the puzzle
		CurrentGuess.Stones.Empty();								// Reset for next guess
	}
}

void AColdStonesPCBase::BeginPlay() 
{
	Super::BeginPlay();
	mygamemode = (AColdStonesGameModeBase*)GetWorld()->GetAuthGameMode();	// Get a pointer to game mode
	if (!mygamemode) return;	// Abort if no game mode is found
	mypuzzle = mygamemode->mypuzzle;
	if (!mypuzzle) return;		// Abort if no puzzle is found
}