// Fill out your copyright notice in the Description page of Project Settings.


#include "ColdStonesPCBase.h"
#include "Kismet/KismetMathLibrary.h"
#include "Blueprint/UserWidget.h"
#include "UObject/Interface.h"

void AColdStonesPCBase::ModifyScoop(UPARAM(ref) EFlavors& inScoop, UPARAM(ref) int ScoopIndex)
{
	if (!mypuzzle) return;													// Make sure a puzzle has been loaded
	CurrentGuess.Scoops[ScoopIndex] = inScoop;								// Append array with passed in stone, construct if necessary
}

void AColdStonesPCBase::ModifyGuessScoop(UPARAM(ref) int attempts) 
{
	if (attempts > 0) 
	{
		BadGuesses.Emplace(CurrentGuess);
		BP_OnAttempt();
	}
	else 
	{
		BadGuesses.Empty();
		BP_OnAttempt();
	}
}

void AColdStonesPCBase::OnCorrect(int correct) 
{
	BP_OnCorrect(correct);
}

void AColdStonesPCBase::Init()												// Puzzle level was loaded, create a starting guess
{
	mygamemode = (AColdStonesGameModeBase*)GetWorld()->GetAuthGameMode();	// Get a pointer to game mode
	if (!mygamemode) return;												// Abort if no game mode is found
	mypuzzle = mygamemode->mypuzzle;										// Get a pointer to the puzzle					
	if (!mypuzzle) return;													// Abort if no puzzle is found
	
	for (int i = 0; i < mygamemode->numstonesperlock; i++)					// Populate guess array to start
	{	
		EFlavors flavor = static_cast<EFlavors>(UKismetMathLibrary::RandomInteger(mygamemode->numstonecolors));
		// Add random scoops to the starting guess
		CurrentGuess.Scoops.Emplace(flavor);
	}
	
	BadGuesses.SetNum(mygamemode->attempts, true);							// Create array of guesses we have tried already


}

void AColdStonesPCBase::BeginPlay() 
{	
	Init();
	if (!mypuzzle) return;
	mypuzzle->OnAttempt.AddDynamic(this, &AColdStonesPCBase::ModifyGuessScoop);
	mypuzzle->OnOpen.AddDynamic(this, &AColdStonesPCBase::OnCorrect);
	Super::BeginPlay();
	
}