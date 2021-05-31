// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstGameStateBase.h"
#include "Net/UnrealNetwork.h"

AFirstGameStateBase::AFirstGameStateBase()
{
}


void AFirstGameStateBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{

	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AFirstGameStateBase, Players);
}
