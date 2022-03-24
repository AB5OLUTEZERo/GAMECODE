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



public:

	/** Returns the network-synced time from the server.
	  * Corresponds to GetWorld()->GetTimeSeconds()
	  * on the server. This doesn't actually make a network
	  * request; it just returns the cached, locally-simulated
	  * and lag-corrected ServerTime value which was synced
	  * with the server at the time of this PlayerController's
	  * last restart. */
	virtual float GetServerTime() { return ServerTime; }

	virtual void ReceivedPlayer() override;

protected:

	/** Reports the current server time to clients in response
	  * to ServerRequestServerTime */
	UFUNCTION(Client, Reliable)
		void ClientReportServerTime(
			float requestWorldTime,
			float serverTime
		);

	/** Requests current server time so accurate lag
	  * compensation can be performed in ClientReportServerTime
	  * based on the round-trip duration */
	UFUNCTION(Server, Reliable, WithValidation)
		void ServerRequestServerTime(
			APlayerController* requester,
			float requestWorldTime
		);





	float ServerTime = 0.0f;

protected:
	virtual void SetupInputComponent() override;

	void StartRace();
	
};
