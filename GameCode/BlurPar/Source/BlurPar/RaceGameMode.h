// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RaceGameMode.generated.h"

/**
 * 
 */


UCLASS()
class BLURPAR_API ARaceGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ARaceGameMode();

	void StartCountDownForAllPlayers();


	void PlayerReacherFinishLine(class  ARacePlayerController* ReachedPC);

protected:
	// Called when the game starts or when spawned
	virtual void StartPlay() override;

	virtual void PostLogin(APlayerController* NewPlayer)override;

	TArray<class  ARacePlayerController*> AllPlayers;

	TArray<class  ARacePlayerController*> FinishList;

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class  ABlurParCharacter> PlayerClass;

	bool RaceStarted;

	void UnfreezeAllPlayers();



};
