// Fill out your copyright notice in the Description page of Project Settings.


#include "ColdStonesGameModeBase.h"
#include "UObject/Interface.h"


AColdStonesGameModeBase::AColdStonesGameModeBase() 
{
	mypuzzle = CreateDefaultSubobject<UPuzzle>("PuzzleInstance");
	if (mypuzzle) 
	{
		mypuzzle->OnGameover.AddDynamic(this, &AColdStonesGameModeBase::BP_OnGameover);
		mypuzzle->OnAttempt.AddDynamic(this, &AColdStonesGameModeBase::BP_OnAttempt);
		mypuzzle->OnOpen.AddDynamic(this, &AColdStonesGameModeBase::BP_OnOpen);
	}
}


void AColdStonesGameModeBase::BeginPlay() 
{
	Super::BeginPlay();
}