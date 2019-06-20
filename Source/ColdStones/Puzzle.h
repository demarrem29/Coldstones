// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ColdStones.h"
#include "Lock.h"
#include "Components/ActorComponent.h"
#include "Puzzle.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COLDSTONES_API UPuzzle : public UActorComponent
{
	GENERATED_BODY()
public:	
	// Declare default values for this component's properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PuzzleProperties)
		int attempts;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PuzzleProperties)
		int locks_opened;
	UPROPERTY(VisibleAnywhere)
		class AColdStonesGameModeBase* mymode;
	TArray<FLock> Locks;
	void init();
	UFUNCTION(BlueprintCallable, Category="PuzzleFunctions")
		int32 guess(struct FLock& inLock);
	UPuzzle();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;	
};
