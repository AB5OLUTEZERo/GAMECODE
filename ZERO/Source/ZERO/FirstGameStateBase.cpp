// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstGameStateBase.h"
#include "Net/UnrealNetwork.h"
#include"FirstPlayerController.h"

AFirstGameStateBase::AFirstGameStateBase()
{
}


void AFirstGameStateBase::EndGame_Implementation()
{
	for (FConstPlayerControllerIterator iter = GetWorld()->GetPlayerControllerIterator(); iter; ++iter)
	{
		//APlayerController *playerController = iter->Get();
		AFirstPlayerController* PC = Cast<AFirstPlayerController>(iter->Get());
		if (PC)
		{
			PC->GameEnded();
			//PC->UnPossess();
		}
		//...
	}
}

void AFirstGameStateBase::BeginPlay()
{
	Super::BeginPlay();
	TeamAKills = 0;

	TeamBKills = 0;

	bGameEnded = false;
}

void AFirstGameStateBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{

	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AFirstGameStateBase, Players);
	DOREPLIFETIME(AFirstGameStateBase, TeamAKills);
	DOREPLIFETIME(AFirstGameStateBase, TeamBKills);
	DOREPLIFETIME(AFirstGameStateBase, WinResult);
	DOREPLIFETIME(AFirstGameStateBase, bGameEnded);
}
