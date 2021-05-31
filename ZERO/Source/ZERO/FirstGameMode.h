// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FirstGameMode.generated.h"

/**
 * 
 */
UCLASS()
class ZERO_API AFirstGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AFirstGameMode();

protected:
	// Called when the game starts or when spawned
	virtual void StartPlay() override;
};
