// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RacePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BLURPAR_API ARacePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	
	
	UFUNCTION(Reliable, Client)
		void DisplayCountDownWidget();

	UFUNCTION(Reliable, Client)
		void UnfreezePlayer();


	UFUNCTION(Reliable, Client)
		void PlayerFinished(int place);


	UPROPERTY(BlueprintReadOnly)
	int PlacedAt;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TSubclassOf<UUserWidget> FinishedWidget;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TSubclassOf<UUserWidget> CountDownWidget;

protected:
	virtual void SetupInputComponent() override;

	void StartRace();
	
};
