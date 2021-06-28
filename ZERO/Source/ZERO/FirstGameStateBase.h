// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "FirstGameStateBase.generated.h"

/**
 * 
 */

class AZEROCharacter;
UCLASS()
class ZERO_API AFirstGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
	

public:
	AFirstGameStateBase();

	UPROPERTY(replicated)
		TArray<AZEROCharacter*> Players;

	UPROPERTY(replicated, BlueprintReadOnly, Category = "GameState")
	int TeamAKills;

	UPROPERTY(replicated, BlueprintReadOnly, Category = "GameState")
	int TeamBKills;

	UPROPERTY(replicated, BlueprintReadOnly, Category = "GameState")
		FString WinResult;

	UPROPERTY(replicated, BlueprintReadOnly, Category = "GameState")
	bool bGameEnded;

	UFUNCTION(NetMulticast, Reliable)
		void EndGame();
protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
