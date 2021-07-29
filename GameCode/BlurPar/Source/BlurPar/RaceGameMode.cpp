// Fill out your copyright notice in the Description page of Project Settings.


#include "RaceGameMode.h"
#include"RacePlayerController.h"
#include"BlurParCharacter.h"
#include"TimerManager.h"

ARaceGameMode::ARaceGameMode()
{
	DefaultPawnClass = nullptr;
	PlayerControllerClass = ARacePlayerController::StaticClass();
}
void ARaceGameMode::StartPlay()
{
	Super::StartPlay();
	RaceStarted = false;
}

void ARaceGameMode::PostLogin(APlayerController * NewPlayer)
{
	Super::PostLogin(NewPlayer);

	ARacePlayerController* RacePC = Cast<ARacePlayerController>(NewPlayer);
	if (RacePC)
	{
		AllPlayers.Add(RacePC);
		AActor* SpawnLocActor = FindPlayerStart(RacePC, FString::FromInt(AllPlayers.Num()));
		if (SpawnLocActor)
		{
			FTransform SpawnTransform;
			SpawnTransform.SetLocation(SpawnLocActor->GetActorLocation());
			//SpawnTransform.SetRotation(SpawnLocActor->GetActorRotation());
			SpawnTransform.SetScale3D(FVector(1, 1, 1));
			FActorSpawnParameters SpawnParams;
			ABlurParCharacter* MyPlayer = GetWorld()->SpawnActor<ABlurParCharacter>(PlayerClass, SpawnLocActor->GetActorLocation(),SpawnLocActor->GetActorRotation(), SpawnParams);
			//MyPlayer->FinishSpawning(SpawnTransform);
			RacePC->Possess(MyPlayer);
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Error");
		}
	}
}

void ARaceGameMode::UnfreezeAllPlayers()
{
	for (int i = 0; i < AllPlayers.Num(); i++)
	{
		AllPlayers[i]->UnfreezePlayer();
	}
	
}

void ARaceGameMode::StartCountDownForAllPlayers()
{
	if (RaceStarted == false)
	{
		for (int i = 0; i < AllPlayers.Num(); i++)
		{
			AllPlayers[i]->DisplayCountDownWidget();
		}
		RaceStarted = true;

		FTimerHandle UnFreezeTimerHandle;

		GetWorldTimerManager().SetTimer(UnFreezeTimerHandle, this, &ARaceGameMode::UnfreezeAllPlayers, 3, false, 3);
	}

}
