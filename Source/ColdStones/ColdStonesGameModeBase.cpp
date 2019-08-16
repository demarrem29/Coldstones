// Fill out your copyright notice in the Description page of Project Settings.


#include "ColdStonesGameModeBase.h"
#include "UObject/Interface.h"


AColdStonesGameModeBase::AColdStonesGameModeBase() 
{
	mypuzzle = CreateDefaultSubobject<UPuzzle>("PuzzleInstance");
	if (mypuzzle) 
	{
		mypuzzle->OnGuess.AddDynamic(this, &AColdStonesGameModeBase::BP_OnGuess);
	}
}


void AColdStonesGameModeBase::BeginPlay() 
{
	Super::BeginPlay();
}