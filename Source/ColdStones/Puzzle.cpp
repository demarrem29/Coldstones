// Fill out your copyright notice in the Description page of Project Settings.


#include "Puzzle.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UPuzzle::UPuzzle()
{
	
}

// Create Puzzle Data Structure
void UPuzzle::init() 
{
	mymode = (AColdStonesGameModeBase*)GetWorld()->GetAuthGameMode();
	if (mymode == nullptr)
	{
		return;
	}
	Locks = new FLock[mymode->numlocks];		// Make sure Locks vector is the correct size
	for (int i = 0; i < mymode->numlocks; i++)  // Instantiate locks
	{
		Locks[i].stones = new FStone[mymode->numstonesperlock];	// Make sure Lock array is the correct size
		for (int j = 0; j < mymode->numstonesperlock; j++) // Instantiate each lock
		{
			Locks[i].stones[j].color = static_cast<EColors>(UKismetMathLibrary::RandomInteger(mymode->numstonecolors)); // Pick a random color from EColors between 1 and numstonecolors
		}

	}
}

// Check if the user input lock is correct
bool UPuzzle::guess(FLock* inLock)
{
	std::vector<int> retval;		// Create return vector and initialize each value with zero.
	std::vector<int> stonematchguess(mymode->numstonesperlock, 0);
	std::vector<int> stonematchactual(mymode->numstonesperlock, 0);
	std::vector<int> correctguess(mymode->numstonesperlock, 2); // Comparison vector for stonematch
	for (int i = 0; i < mymode->numstonesperlock; i++)			// Iterate through guess lock, looking for perfect matches first
	{
		if (inLock->stones[i].color == Locks[locks_opened].stones[i].color) // Exact match found
		{
			retval.push_back(2);
			stonematchguess[i] = 1;
			stonematchactual[i] = 1;
		}
	}
	for (int i = 0; i < mymode->numstonesperlock; i++)			// Iterate through guess lock, looking for partial matches
	{
		if (stonematchguess[i] == 0)					// Skip over stones from guess that have already been matched
		{
			for (int j = 0; j < mymode->numstonesperlock; j++)
			{
				if (stonematchactual[j] == 0)			// Skip over stones from puzzle that have already been matched
				{
					if (inLock->stones[i].color == Locks[locks_opened].stones[j].color) // Partial match found
					{
						retval.push_back(1);
						stonematchguess[i] = 1;
						stonematchactual[j] = 1;
					}
				}

			}

		}
		if (stonematchguess[i] == 0) retval.push_back(0);	// If no matches were found, mark it zero
	}
	if (retval == correctguess)													// If the guess was perfect
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
	return mymode->gameover;
}

// Called when the game starts
void UPuzzle::BeginPlay()
{
	Super::BeginPlay(); 
	init();
	// ...
	
}


// Called every frame
void UPuzzle::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

