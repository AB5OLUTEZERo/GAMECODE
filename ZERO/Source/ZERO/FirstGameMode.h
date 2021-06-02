// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include"ZERO.h"
#include "FirstGameMode.generated.h"


class AZEROCharacter;
class AFirstPlayerController;
/**
 * 
 */
UCLASS()
class ZERO_API AFirstGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AFirstGameMode();


	UFUNCTION()
		void RequestSpawn(ETeamID TeamID, AFirstPlayerController* ControllerRef);


	UFUNCTION()
		void RequestCharacterSpawn(TSubclassOf<AZEROCharacter> PlayerClass, ETeamID TeamID, AFirstPlayerController* ControllerRef);

	
protected:
	// Called when the game starts or when spawned
	virtual void StartPlay() override;


	
};
