// Fill out your copyright notice in the Description page of Project Settings.


#include "RacePlayerController.h"
#include "Components/Widget.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include"RaceGameMode.h"
#include "Engine/World.h"
#include"RaceGameStateBase.h"

	

void ARacePlayerController::DisplayCountDownWidget_Implementation()
{
	if (CountDownWidget)
	{
		UUserWidget* MyCountDown = CreateWidget<UUserWidget>(this, CountDownWidget);
		if (MyCountDown)
		{

			MyCountDown->AddToViewport();

		}

	}
}

void ARacePlayerController::UnfreezePlayer_Implementation()
{
	GetPawn()->EnableInput(this);
	
}



void ARacePlayerController::PlayerFinished_Implementation(int place)
{
	GetPawn()->DisableInput(this);
	PlacedAt = place;
	if (FinishedWidget)
	{
		UUserWidget* MyFinished = CreateWidget<UUserWidget>(this, FinishedWidget);
		if (MyFinished)
		{

			MyFinished->AddToViewport();

		}

	}

}

void ARacePlayerController::ServerRequestServerTime_Implementation(
	APlayerController* requester,
	float requestWorldTime
)
{
	float serverTime = GetWorld()->GetGameState()->GetServerWorldTimeSeconds();

	ClientReportServerTime(requestWorldTime, serverTime);
}

bool ARacePlayerController::ServerRequestServerTime_Validate(
	APlayerController* requester,
	float requestWorldTime
)
{
	return true;
}

void ARacePlayerController::ClientReportServerTime_Implementation(
	float requestWorldTime,
	float serverTime
)
{
	// Apply the round-trip request time to the server's         
	// reported time to get the up-to-date server time
	float roundTripTime = GetWorld()->GetTimeSeconds() -
		requestWorldTime;
	float adjustedTime = serverTime + (roundTripTime * 0.5f);
	ServerTime = adjustedTime;
}
void ARacePlayerController::ReceivedPlayer()
{
	Super::ReceivedPlayer();

	if (IsLocalController())
	{
		ServerRequestServerTime(
			this,
			GetWorld()->GetTimeSeconds()
		);
	}
}

void ARacePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	check(InputComponent);

	InputComponent->BindAction("Start", IE_Pressed, this, &ARacePlayerController::StartRace);
	
}

void ARacePlayerController::StartRace()
{
	if (HasAuthority())
	{
		ARaceGameMode* MyGameMode = Cast<ARaceGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		if (MyGameMode)
		{
			MyGameMode->StartCountDownForAllPlayers();
		}
	}
}
