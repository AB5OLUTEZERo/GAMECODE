// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstPlayerState.h"
#include "Net/UnrealNetwork.h"

void AFirstPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AFirstPlayerState,Kills);
}
