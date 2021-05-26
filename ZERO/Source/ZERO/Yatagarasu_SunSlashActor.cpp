// Fill out your copyright notice in the Description page of Project Settings.


#include "Yatagarasu_SunSlashActor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include"DrawDebugHelpers.h"

// Sets default values
AYatagarasu_SunSlashActor::AYatagarasu_SunSlashActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSceneComponent"));
	}

	// Use a sphere as a simple collision representation.
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	// Set the sphere's collision radius.
	CollisionComp->InitSphereRadius(15.0f);
	// Set the root component to be the collision component.
	RootComponent = CollisionComp;



	//CollisionComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//CollisionComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	CollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	//CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AYatagarasu_SunSlash_Actor::SlashOnOverlapBegin);


	// Use this component to drive this projectile's movement.
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->SetUpdatedComponent(CollisionComp);
	ProjectileMovementComponent->InitialSpeed = 1500.0f;
	ProjectileMovementComponent->MaxSpeed = 3000.0f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = true;
	ProjectileMovementComponent->Bounciness = 0.3f;
	ProjectileMovementComponent->ProjectileGravityScale = 0.0f;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(RootComponent);


	bReplicates = true;
	SetReplicates(true);
	SetReplicateMovement(true);


	InterpolScale = 0.75;
	DesieredScale = FVector(10, 10, 10);

}

void AYatagarasu_SunSlashActor::FireInDirection(const FVector & ShootDirection)
{
}

// Called when the game starts or when spawned
void AYatagarasu_SunSlashActor::BeginPlay()
{
	Super::BeginPlay();
	
	
}

// Called every frame
void AYatagarasu_SunSlashActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SetActorScale3D(FMath::VInterpTo(GetActorScale3D(), DesieredScale, DeltaTime, InterpolScale));

}

