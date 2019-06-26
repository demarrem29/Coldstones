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
	mymode->initialized = false;
	attempts = 0;
	locks_opened = 0;
	mymode->mypuzzle = this;					// Give the gamemode a pointer to us
	for (int i = 0; i < mymode->numlocks; i++)  // Instantiate locks
	{
		FCone * tempcone = new FCone;
		if (!tempcone) return;
		Cones.Add(*tempcone);	// Append lock array with a new lock reference
		for (int j = 0; j < mymode->numstonesperlock; j++) // Instantiate each lock
		{
			Cones[i].Scoops.Add(static_cast<EFlavors>(UKismetMathLibrary::RandomInteger(mymode->numstonecolors))); // Pick a random flavor from EFlavors and add to array
		}
		
	}
	mymode->initialized = true;
}

// Game mode sends user's guess and puzzle compares it to itself
void UPuzzle::guess(UPARAM(ref) struct FCone& inCone)
{
	FCone *GuessCone = &inCone;					// Dereference pointer from input
	if (!GuessCone) return;				// Check pointer before accessing
	if (!mymode) return;					// Check mode pointer before accessing
	
	// Reset guess variables
	numconescorrect = 0;
	numflavorscorrect = 0;

	int* stonematchguess = new int[mymode->numstonesperlock];	// Which stones from guess have already been matched this iteration
	int* stonematchactual = new int[mymode->numstonesperlock];	// Which stones from lock have already been matched this iteration
	for (int i = 0; i < mymode->numstonesperlock; i++)			// Iterate through guess lock, looking for perfect matches first
	{
		if (GuessCone->Scoops[i] == Cones[locks_opened].Scoops[i]) // Exact match found
		{
			numconescorrect++;
			stonematchguess[i] = 1;
			stonematchactual[i] = 1;
		}
		else 
		{
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
					if (GuessCone->Scoops[i] == Cones[locks_opened].Scoops[j]) // Partial match found
					{
						numflavorscorrect++;
						stonematchguess[i] = 1;
						stonematchactual[j] = 1;
					}
				}

			}

		}
	}
	if (numconescorrect == mymode->numstonesperlock)													// If the guess was perfect
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
	return;
}

// Called when the game starts
void UPuzzle::BeginPlay()
{
	Super::BeginPlay(); 
	init();
	// ...
	
}

