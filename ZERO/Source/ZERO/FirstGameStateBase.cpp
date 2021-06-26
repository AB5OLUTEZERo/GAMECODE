// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstGameStateBase.h"
#include "Net/UnrealNetwork.h"

AFirstGameStateBase::AFirstGameStateBase()
{
}


void AFirstGameStateBase::BeginPlay()
{
	Super::BeginPlay();
	TeamAKills = 0;

	TeamBKills = 0;
}

void AFirstGameStateBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{

	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AFirstGameStateBase, Players);
	DOREPLIFETIME(AFirstGameStateBase, TeamAKills);
	DOREPLIFETIME(AFirstGameStateBase, TeamBKills);
	DOREPLIFETIME(AFirstGameStateBase, WinResult);
}
