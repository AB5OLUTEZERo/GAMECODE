// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "FirstGameStateBase.generated.h"

/**
 * 
 */

class AZEROCharacter;
UCLASS()
class ZERO_API AFirstGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
	

public:
	AFirstGameStateBase();

	UPROPERTY(replicated)
		TArray<AZEROCharacter*> Players;

protected:
	


	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
