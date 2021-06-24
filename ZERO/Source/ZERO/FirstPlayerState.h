// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "FirstPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class ZERO_API AFirstPlayerState : public APlayerState
{
	GENERATED_BODY()


public:

	UPROPERTY(replicated,BlueprintReadOnly, Category = "KDA")
	float Kills;


protected:

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;



	


};
