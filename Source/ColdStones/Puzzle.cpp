// Fill out your copyright notice in the Description page of Project Settings.


#include "Puzzle.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UPuzzle::UPuzzle()
{
	
}

// Create Puzzle Data Structure, initialize class variables
void UPuzzle::init() 
{
	mymode = (AColdStonesGameModeBase*)GetWorld()->GetAuthGameMode();	// Get a pointer to game mode
	if (!mymode)	// Abort if no game mode is found
	{
		return;
	}
	attempts = 0;
	locks_opened = 0;
	mymode->mypuzzle = this;					// Give the gamemode a pointer to us
	for (int i = 0; i < mymode->numlocks; i++)  // Instantiate locks
	{
		FLock * templock = new FLock;
		if (!templock) return;
		Locks.Add(*templock);	// Append lock array with a new lock reference
		for (int j = 0; j < mymode->numstonesperlock; j++) // Instantiate each lock
		{
			FStone * tempstone = new FStone;
			if (!tempstone) return;
			Locks[i].Stones.Add(*tempstone); // Pick a random color from EColors between 1 and numstonecolors
			Locks[i].Stones[j].color = static_cast<EColors>(UKismetMathLibrary::RandomInteger(mymode->numstonecolors));
		}
		
	}
}

// Game mode sends user's guess and puzzle compares it to itself
int32 UPuzzle::guess(UPARAM(ref) struct FLock& inLock)
{
	FLock *Lock = &inLock;					// Dereference pointer from input
	if (!Lock) return NULL;						// Check pointer before accessing
	if (!mymode) return NULL;					// Check mode pointer before accessing
	
	int32* retval = new int[mymode->numstonesperlock];		// Create return array
	int* stonematchguess = new int[mymode->numstonesperlock];	// Which stones from guess have already been matched this iteration
	int* stonematchactual = new int[mymode->numstonesperlock];	// Which stones from lock have already been matched this iteration
	int* correctguess = new int[mymode->numstonesperlock]; // Comparison array for stonematch
	for (int i = 0; i < mymode->numstonesperlock; i++)			// Iterate through guess lock, looking for perfect matches first
	{
		correctguess[i] = 2;
		if (Lock[0].Stones[i].color == Locks[locks_opened].Stones[i].color) // Exact match found
		{
			retval[i] = 2;
			stonematchguess[i] = 1;
			stonematchactual[i] = 1;
		}
		else 
		{
			retval[i] = 0;
			stonematchguess[i] = 0;
			stonematchactual[i] = 0;
		}
	}
	for (int i = 0; i < mymode->numstonesperlock; i++)			// Iterate through guess lock, looking for partial matches
	{
		if (stonematchguess[i] == 0)					// Skip over stones from guess that have already been matched from previous loop
		{
			for (int j = 0; j < mymode->numstonesperlock; j++)
			{
				if (stonematchactual[j] == 0)			// Skip over stones from puzzle that have already been matched
				{
					if (Lock[0].Stones[i].color == Locks[locks_opened].Stones[j].color) // Partial match found
					{
						retval[i] = 1;
						stonematchguess[i] = 1;
						stonematchactual[j] = 1;
					}
				}

			}

		}
		if (stonematchguess[i] == 0) retval[i] = 0;	// If no matches were found, mark it zero
	}
	if (*retval == *correctguess)													// If the guess was perfect
	{
		// Move on to next lock
		locks_opened++;
		attempts = 0;
		if (locks_opened >= mymode->numlocks)												// If that was the last lock, win instead
		{
			mymode->win = true;
			mymode->gameover = true;
		}
	}
	else
	{
		attempts++;
		if (attempts >= mymode->numattempts)
		{
			mymode->win = false;
			mymode->gameover = true;
			attempts = 0;
		}
	}
	return *retval;
}

// Called when the game starts
void UPuzzle::BeginPlay()
{
	Super::BeginPlay(); 
	init();
	// ...
	
}

