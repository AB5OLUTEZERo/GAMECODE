// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Yatagarasu_SunSlashActor.generated.h"

UCLASS()
class ZERO_API AYatagarasu_SunSlashActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AYatagarasu_SunSlashActor();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		class USphereComponent* CollisionComp;

	UPROPERTY(VisibleAnywhere, Category = Movement)
		class UProjectileMovementComponent* ProjectileMovementComponent;


	UPROPERTY(VisibleAnywhere, Category = Mesh)
		class UStaticMeshComponent* MeshComp;

	void FireInDirection(const FVector& ShootDirection);





	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Scale")
		FVector DesieredScale;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Scale")
		float InterpolScale;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
