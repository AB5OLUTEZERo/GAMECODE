// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstGameMode.h"
#include"FirstPlayerController.h"
#include"FirstGameState.h"
#include "ZEROCharacter.h"
#include "Kismet/GameplayStatics.h"
#include"FirstGameInstance.h"
#include"FirstGameStateBase.h"

AFirstGameMode::AFirstGameMode()
	
{
	DefaultPawnClass = nullptr;
	PlayerControllerClass = AFirstPlayerController::StaticClass();
	
}



void AFirstGameMode::RequestSpawn(ETeamID TeamID, AFirstPlayerController * ControllerRef)
{
	
}

void AFirstGameMode::RequestCharacterSpawn(TSubclassOf<AZEROCharacter> PlayerClass, ETeamID TeamID, AFirstPlayerController * ControllerRef)
{
	if (PlayerClass)
	{
		
		FTransform SpawnTransform;
		if (TeamID == ETeamID::TeamA)
		{
			TeamAPlayers.AddUnique(ControllerRef);
			SpawnTransform.SetLocation(TeamAStartLocation);
		}
		else if (TeamID == ETeamID::TeamB)
		{
			TeamBPlayers.AddUnique(ControllerRef);
			SpawnTransform.SetLocation(TeamBStartLocation);
			
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Black, "Error");
		}
		SpawnTransform.SetScale3D(FVector(1, 1, 1));
		AZEROCharacter* MyPlayer = GetWorld()->SpawnActorDeferred<AZEROCharacter>(PlayerClass, SpawnTransform);
		MyPlayer->SetTeamBeforeSpawn(TeamID);
		MyPlayer->FinishSpawning(SpawnTransform);
		AddPlayerToTeamList(TeamID, ControllerRef);
		ControllerRef->Possess(MyPlayer);
		AddPlayerToTeamList(TeamID, ControllerRef);

	}
}

void AFirstGameMode::AddPlayerToTeamList(ETeamID TeamID, AFirstPlayerController * ControllerRef)
{
	if (TeamID == ETeamID::TeamA)
	{
		TeamAPlayers.AddUnique(ControllerRef);
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, "A");
	}
	else if (TeamID == ETeamID::TeamB)
	{
		TeamBPlayers.AddUnique(ControllerRef);
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "B");
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Black, "Error");
	}
}

void AFirstGameMode::AddAndCheckIfKillCountReachedLimit(ETeamID TeamID)
{
	AFirstGameStateBase* MyGameState = Cast<AFirstGameStateBase>(GameState);
	if (MyGameState)
	{
		if (TeamID == ETeamID::TeamA)
		{
			TeamAKills += 1;
			MyGameState->TeamAKills += 1;
			if (TeamAKills >= 3)
			{

				TheEndGame(TeamID);
			}
		}
		else if (TeamID == ETeamID::TeamB)
		{
			TeamBKills += 1;
			MyGameState->TeamBKills += 1;
			if (TeamBKills >= 3)
			{
				TheEndGame(TeamID);
			}
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Black, "Error");
		}
	}
}

int AFirstGameMode::GetTeamKillCount(ETeamID TeamID)
{
	if (TeamID == ETeamID::TeamA)
	{
		return TeamAKills;
	}
	else if (TeamID == ETeamID::TeamB)
	{
		return TeamBKills;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Black, "Error");
		return 0;
	}
}



void AFirstGameMode::StartPlay()
{
	
	Super::StartPlay();
	TeamAKills = 0;
	TeamBKills = 0;
	UFirstGameInstance* MyGameInstance = Cast<UFirstGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (MyGameInstance)
	{
		if (MyGameInstance->TeamID == ETeamID::None)
		{
			
		}
		else if(MyGameInstance->TeamID == ETeamID::TeamA)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, "TeamA");
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, "TeamB");
		}
	}
	
}

void AFirstGameMode::TheEndGame(ETeamID TeamID)
{
	AFirstGameStateBase* MyGameState = Cast<AFirstGameStateBase>(GameState);
	if (MyGameState)
	{
		if (TeamID == ETeamID::None)
		{
			MyGameState->WinResult = "No Winner";
		}
		else if (TeamID == ETeamID::TeamA)
		{
			MyGameState->WinResult = "Team A Wins";
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, "TeamA Won");
		}
		else
		{
			MyGameState->WinResult = "Team B Wins";
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "TeamB Won");
		}
	}
	
	
}
