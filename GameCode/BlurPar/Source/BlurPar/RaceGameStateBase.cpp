// Fill out your copyright notice in the Description page of Project Settings.


#include "RaceGameStateBase.h"
#include"RacePlayerController.h"

float ARaceGameStateBase::GetServerWorldTimeSeconds() const
{
	if (ARacePlayerController* pc =  Cast<ARacePlayerController>(GetGameInstance()->GetFirstLocalPlayerController(GetWorld()))
		)
	{
		return pc->GetServerTime();
	}
	else
	{
		return GetWorld()->GetTimeSeconds();
	}
}