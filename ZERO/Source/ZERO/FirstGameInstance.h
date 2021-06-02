// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include"ZERO.h"
#include "FirstGameInstance.generated.h"

/**
 * 
 */
class AZEROCharacter;
UCLASS()
class ZERO_API UFirstGameInstance : public UGameInstance
{
	GENERATED_BODY()
	

		


public:

	UFirstGameInstance();

		ETeamID TeamID;

		TSubclassOf<AZEROCharacter> PlayerClass;
};
