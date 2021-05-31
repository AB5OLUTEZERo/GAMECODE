// Fill out your copyright notice in the Description page of Project Settings.


#include "LoadCameraPawn.h"
#include "Camera/CameraComponent.h"


// Sets default values
ALoadCameraPawn::ALoadCameraPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->AttachTo(RootComponent);
}

// Called when the game starts or when spawned
void ALoadCameraPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALoadCameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ALoadCameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

