// Fill out your copyright notice in the Description page of Project Settings.


#include "ColdStonesGameModeBase.h"
#include "UObject/Interface.h"

void AColdStonesGameModeBase::BeginPlay() 
{
	Super::BeginPlay();
	OnGameover.AddDynamic(this, &AColdStonesGameModeBase::BP_OnGameover);
	OnWin.AddDynamic(this, &AColdStonesGameModeBase::BP_OnWin);
}