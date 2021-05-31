// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FirstPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ZERO_API AFirstPlayerController : public APlayerController
{
	GENERATED_BODY()
	

public:

	AFirstPlayerController();


	
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TSubclassOf<UUserWidget> MenuWidget;

	


};
