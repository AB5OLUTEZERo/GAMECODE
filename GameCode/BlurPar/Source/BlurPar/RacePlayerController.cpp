// Fill out your copyright notice in the Description page of Project Settings.


#include "RacePlayerController.h"
#include "Components/Widget.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include"RaceGameMode.h"

	

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
