// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstGameMode.h"
#include"FirstPlayerController.h"
#include"FirstGameState.h"
#include "ZEROCharacter.h"

AFirstGameMode::AFirstGameMode()
	
{
	DefaultPawnClass = nullptr;
	PlayerControllerClass = AFirstPlayerController::StaticClass();
	
}



void AFirstGameMode::RequestSpawn(ETeamID TeamID, AFirstPlayerController * ControllerRef)
{
	if (PlayerClass)
	{
		UWorld* MyWorld = GetWorld();

		if (TeamID == ETeamID::TeamA)
		{
			FVector SpawnLocation = FVector(-912.002502, -338.000000, 222.001526);

			FTransform SpawnTransform;
			SpawnTransform.SetLocation(SpawnLocation);
			SpawnTransform.SetScale3D(FVector(1, 1, 1));
			AZEROCharacter* Player = MyWorld->SpawnActorDeferred<AZEROCharacter>(PlayerClass, SpawnTransform);
			Player->SetTeamBeforeSpawn(TeamID);
			Player->FinishSpawning(SpawnTransform);
			ControllerRef->Possess(Player);

		}
		else if (TeamID == ETeamID::TeamB)
		{
			FVector SpawnLocation = FVector(-912.002502,  924.000000, 222.001526);

			FTransform SpawnTransform;
			SpawnTransform.SetLocation(SpawnLocation);
			SpawnTransform.SetScale3D(FVector(1, 1, 1));
			AZEROCharacter* Player = MyWorld->SpawnActorDeferred<AZEROCharacter>(PlayerClass, SpawnTransform);
			Player->SetTeamBeforeSpawn(TeamID);
			Player->FinishSpawning(SpawnTransform);
			ControllerRef->Possess(Player);
		}
		else
		{

		}
	}
}

void AFirstGameMode::StartPlay()
{
	
	Super::StartPlay();
	
}
