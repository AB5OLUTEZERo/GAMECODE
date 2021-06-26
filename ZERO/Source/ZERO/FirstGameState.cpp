// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstGameState.h"
#include "Net/UnrealNetwork.h"

AFirstGameState::AFirstGameState()
{
	bReplicates = true;
	bAlwaysRelevant = true;
}
void AFirstGameState::BeginPlay()
{
	Super::BeginPlay();
	TeamAKills=0;

	 TeamBKills=0;
}

void AFirstGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	DOREPLIFETIME(AFirstGameState, Players);
}
