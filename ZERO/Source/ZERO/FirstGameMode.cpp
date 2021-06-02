// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstGameMode.h"
#include"FirstPlayerController.h"
#include"FirstGameState.h"
#include "ZEROCharacter.h"
#include "Kismet/GameplayStatics.h"
#include"FirstGameInstance.h"

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
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, "A");
			SpawnTransform.SetLocation(FVector(-912.002502, 924.000000, 222.001526));
		}
		else if (TeamID == ETeamID::TeamB)
		{
			SpawnTransform.SetLocation(FVector(-912.002502, -1301.000000, 222.001526));
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "B");
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Black, "RepFire");
		}
		SpawnTransform.SetScale3D(FVector(1, 1, 1));
		AZEROCharacter* MyPlayer = GetWorld()->SpawnActorDeferred<AZEROCharacter>(PlayerClass, SpawnTransform);
		MyPlayer->SetTeamBeforeSpawn(TeamID);
		MyPlayer->FinishSpawning(SpawnTransform);

		ControllerRef->Possess(MyPlayer);
	}
}

void AFirstGameMode::StartPlay()
{
	
	Super::StartPlay();
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
