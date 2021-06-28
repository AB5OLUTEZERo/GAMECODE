// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include"ZERO.h"
#include "FirstPlayerController.generated.h"

/**
 * 
 */
class AZEROCharacter;
UCLASS()
class ZERO_API AFirstPlayerController : public APlayerController
{
	GENERATED_BODY()
	

public:

	AFirstPlayerController();


	UFUNCTION(Reliable, Server, BlueprintCallable,Category="TeamSelection")
		void TeamSelected(ETeamID TeamID);

	UFUNCTION(Reliable, Server, BlueprintCallable, Category = "CharacterSelection")
		void CharacterSelected(TSubclassOf<AZEROCharacter> PlayerClass);


	
	ETeamID TID;

	FString WinResult;

	TSubclassOf<AZEROCharacter> PCPlayerClass;

	FTimerHandle RespawnTimer;
	UFUNCTION()
		void RespawnStart();

	UFUNCTION(Client, Reliable)
		void GameEnded();

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TSubclassOf<UUserWidget> CharSelectWidget;

	
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TSubclassOf<UUserWidget> MenuWidget;


	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TSubclassOf<UUserWidget> GameOverWidget;


	UFUNCTION()
		void Respawn();


	


};
