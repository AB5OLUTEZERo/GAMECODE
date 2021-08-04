// Fill out your copyright notice in the Description page of Project Settings.


#include "FinishLine.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include"RaceGameMode.h"
#include"RacePlayerController.h"
#include"BlurParCharacter.h"

// Sets default values
AFinishLine::AFinishLine()
{

	FinishLineOverlapComp = CreateDefaultSubobject<UBoxComponent>(TEXT("FinishLineOverlapComp"));
	FinishLineOverlapComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	RootComponent = FinishLineOverlapComp;

	FinishLineOverlapComp->OnComponentBeginOverlap.AddDynamic(this, &AFinishLine::OnBoxBeginOverlap);

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(RootComponent);
	
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AFinishLine::OnBoxBeginOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	
	ABlurParCharacter* BPOverlapedActor = Cast<ABlurParCharacter>(OtherActor);
	if (BPOverlapedActor)
	{
		ARaceGameMode* MyGameMode = Cast<ARaceGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		if (MyGameMode)
		{
			
			MyGameMode->PlayerReacherFinishLine(BPOverlapedActor->GetPlayerController());
		}
		
	}
}

// Called when the game starts or when spawned
void AFinishLine::BeginPlay()
{
	Super::BeginPlay();
	FinishLineOverlapComp->OnComponentBeginOverlap.AddDynamic(this, &AFinishLine::OnBoxBeginOverlap);
}

// Called every frame
void AFinishLine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

