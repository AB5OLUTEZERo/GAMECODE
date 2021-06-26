// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include"LoadCameraPawn.h"
#include "Components/Widget.h"
#include "Blueprint/UserWidget.h"
#include"FirstGameMode.h"
#include"FirstGameInstance.h"
#include"TimerManager.h"


AFirstPlayerController::AFirstPlayerController()
{
	
}
void AFirstPlayerController::TeamSelected_Implementation(ETeamID TeamID)
{
	TID = TeamID;
}
void AFirstPlayerController::CharacterSelected_Implementation(TSubclassOf<AZEROCharacter> PlayerClass)
{
	
	/*FInputModeGameAndUI InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
	InputMode.SetHideCursorDuringCapture(false);
	SetInputMode(InputMode);
	bShowMouseCursor = false;*/
	bShowMouseCursor = false;
	AFirstGameMode* MyGameMode = Cast<AFirstGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (MyGameMode)
	{
		PCPlayerClass = PlayerClass;
		MyGameMode->RequestCharacterSpawn(PlayerClass, TID, this);
		
	}

}


void AFirstPlayerController::Respawn()
{
	AFirstGameMode* MyGameMode = Cast<AFirstGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (MyGameMode)
	{
		
		MyGameMode->RequestCharacterSpawn(PCPlayerClass, TID, this);

	}
}



void AFirstPlayerController::RespawnStart()
{
	
	GetWorldTimerManager().SetTimer(RespawnTimer, this, &AFirstPlayerController::Respawn, 3.0f, false, 3.0);
}





void AFirstPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (HasAuthority())
	{
		TArray<AActor*> _TempArryActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ALoadCameraPawn::StaticClass(), _TempArryActors);
		if (_TempArryActors.IsValidIndex(0))
		{
			ALoadCameraPawn* PawnToPossess = Cast<ALoadCameraPawn>(_TempArryActors[0]);
			if (PawnToPossess)
			{
				Possess(PawnToPossess);
			}
		}
	}
	if (MenuWidget)
	{
		//bShowMouseCursor = true;
		if(IsLocalController())
		{
			UUserWidget* MyMenu = CreateWidget<UUserWidget>(this, MenuWidget);
			if (MyMenu)
			{
				MyMenu->AddToViewport();

				//FInputModeUIOnly InputModeData;
				//// Step 2 config is specific to the type
				//
				//InputModeData.SetWidgetToFocus(MyMenu->TakeWidget()); //Because UMG wraps Slate

				//// Step 3 set the mode for the player controller
				////SetInputMode(InputModeData);
			
				//// Step 4 enable cursor so you know what to click on:
				//bShowMouseCursor = true;
			}
		}
	}

	
	
}
