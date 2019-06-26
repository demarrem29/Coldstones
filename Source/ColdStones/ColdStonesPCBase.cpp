// Fill out your copyright notice in the Description page of Project Settings.


#include "ColdStonesPCBase.h"
#include "Kismet/KismetMathLibrary.h"
#include "Blueprint/UserWidget.h"

void AColdStonesPCBase::ModifyScoop(UPARAM(ref) EFlavors& inScoop, UPARAM(ref) int ScoopIndex)
{
	if (!mypuzzle) return;											// Make sure a puzzle has been loaded
	CurrentGuess.Scoops[ScoopIndex] = inScoop;						// Append array with passed in stone, construct if necessary
}

void AColdStonesPCBase::Init()									// Puzzle level was loaded, create a starting guess
{
	if (!mygamemode) return;
	mypuzzle = mygamemode->mypuzzle;
	if (!mypuzzle) return;
	for (int i = 0; i < mygamemode->numstonesperlock; i++) 
	{	
		EFlavors flavor = static_cast<EFlavors>(UKismetMathLibrary::RandomInteger(mygamemode->numstonecolors));
		// Add random scoops to the starting guess
		CurrentGuess.Scoops.Emplace(flavor);
	}
}

void AColdStonesPCBase::BeginPlay() 
{
	Super::BeginPlay();
	mygamemode = (AColdStonesGameModeBase*)GetWorld()->GetAuthGameMode();	// Get a pointer to game mode
	Init();
	if (!mygamemode) return;	// Abort if no game mode is found
}