// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "FirstGameState.generated.h"

/**
 * 
 */

class AZEROCharacter;
UCLASS()
class ZERO_API AFirstGameState : public AGameState
{
	GENERATED_BODY()
	

public:
	AFirstGameState();

	UPROPERTY(replicated)
	TArray<AZEROCharacter*> Players;

	int TeamAKills;

	int TeamBKills;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
