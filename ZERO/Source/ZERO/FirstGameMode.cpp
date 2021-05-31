// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstGameMode.h"
#include"FirstPlayerController.h"
#include"FirstGameState.h"

AFirstGameMode::AFirstGameMode()
	
{
	DefaultPawnClass = nullptr;
	PlayerControllerClass = AFirstPlayerController::StaticClass();
	
}

void AFirstGameMode::StartPlay()
{
	
	Super::StartPlay();
	
}
