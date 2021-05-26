// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_BaseProjectileAndWaitForEvent.h"
#include"ZEROCharacter.h"
#include"DrawDebugHelpers.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include"BaseChar_AbilitySystemComponent.h"


UGA_BaseProjectileAndWaitForEvent::UGA_BaseProjectileAndWaitForEvent()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;

	AbilityInputID = EGASAbilityInputID::Primary_Attack;


	MuzzleLocationName = "Muzzle";
}
void UGA_BaseProjectileAndWaitForEvent::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo * ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData * TriggerEventData)
{
	CommitAbility(Handle, ActorInfo, ActivationInfo);
	UAnimMontage* MontageToPlay = AttackMontage;
	Hero = Cast<	AZEROCharacter>(GetAvatarActorFromActorInfo());
	if (Hero)
	{

		FString MeleeStartSection = "Throw" ;
		//FName MontageSectionName = FName(*MeleeStartSection);
		Task = UAT_PlayMontageAndWaitForEvent::PlayMontageAndWaitForEvent(this, NAME_None, MontageToPlay, FGameplayTagContainer(), 1.0f, FName(*MeleeStartSection), false, 1.0f);
		Task->OnBlendOut.AddDynamic(this, &UGA_BaseProjectileAndWaitForEvent::OnCompletedOrOnCancelled);
		Task->OnCompleted.AddDynamic(this, &UGA_BaseProjectileAndWaitForEvent::OnCompletedOrOnCancelled);
		Task->OnInterrupted.AddDynamic(this, &UGA_BaseProjectileAndWaitForEvent::OnCompletedOrOnCancelled);
		Task->OnCancelled.AddDynamic(this, &UGA_BaseProjectileAndWaitForEvent::OnCompletedOrOnCancelled);
		Task->EventReceived.AddDynamic(this, &UGA_BaseProjectileAndWaitForEvent::EventReceived);
		// ReadyForActivation() is how you activate the AbilityTask in C++. Blueprint has magic from K2Node_LatentGameplayTaskCall that will automatically call ReadyForActivation().
		Task->ReadyForActivation();
	}
	else
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
	}
}

void UGA_BaseProjectileAndWaitForEvent::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo * ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{

	
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UGA_BaseProjectileAndWaitForEvent::OnCompletedOrOnCancelled(FGameplayTag EventTag, FGameplayEventData EventData)
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
}

void UGA_BaseProjectileAndWaitForEvent::EventReceived(FGameplayTag EventTag, FGameplayEventData EventData)
{
	if (ProjectileClass)
	{
		// Get the camera transform.
		
		FVector CameraLocation = Hero->GetMesh()->GetSocketLocation(FName(*MuzzleLocationName));;
		FRotator CameraRotation = Hero->GetActorRotation();
		// Hero->GetActorEyesViewPoint(CameraLocation, CameraRotation);

		 // Set MuzzleOffset to spawn projectiles slightly in front of the camera.
		MuzzleOffset.Set(100.0f, 0.0f, 0.0f);

		// Transform MuzzleOffset from camera space to world space.
		FVector MuzzleLocation = CameraLocation + (Hero->GetActorForwardVector() * 25);

		// Skew the aim to be slightly upwards.
		FRotator MuzzleRotation = CameraRotation;
		//MuzzleRotation.Pitch += 10.0f;
		//Hero->IncrementComboCount();

		UWorld* World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = Hero;
			SpawnParams.Instigator = Hero->GetInstigator();

			if (GetCurrentActivationInfo().ActivationMode == EGameplayAbilityActivationMode::Authority)
			{
				if (!Projectile)
				{
					// Spawn the projectile at the muzzle.
				  //  GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, "RepFire");
					Projectile = World->SpawnActor<AGAS_HitActor>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
					Projectile->SetOwner(GetAvatarActorFromActorInfo());
					FGameplayCueParameters ImpactParams;
					ImpactParams.Location = Hero->GetActorLocation();
					

						FGameplayTag TagImpact = FGameplayTag::RequestGameplayTag(FName(GCTagForMuzzle));

					Hero->GetAbilitySystemComponent()->AddGameplayCue(TagImpact, ImpactParams);
					if (Projectile)
					{
						GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Orange, "Fire");

						// Set the projectile's initial trajectory.

						

						FVector LaunchDirection = MuzzleRotation.Vector();
						Projectile->FireInDirection(LaunchDirection);

						Projectile->OnDestroyed.AddDynamic(this, &UGA_BaseProjectileAndWaitForEvent::ProjectileDestroyed);
						FGameplayTag TagX = FGameplayTag::RequestGameplayTag(FName("Weapon.Projectile.Hit"));
						TaskHit = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, TagX);
						TaskHit->EventReceived.AddDynamic(this, &UGA_BaseProjectileAndWaitForEvent::HitEventReceived);
						TaskHit->ReadyForActivation();

						

					}
					else
					{
						EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);

					}
				}
			}



		}
		else
		{
			EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);

		}
	}
	else
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);

	}
	FGameplayTag TagX = FGameplayTag::RequestGameplayTag(FName("Weapon.Projectile.Hit"));
	TaskHit = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, TagX);
	TaskHit->EventReceived.AddDynamic(this, &UGA_BaseProjectileAndWaitForEvent::HitEventReceived);
	TaskHit->ReadyForActivation();
	
}

void UGA_BaseProjectileAndWaitForEvent::HitEventReceived(FGameplayEventData EventData)
{
	FGameplayAbilityTargetDataHandle Handle;
	Handle.Append(EventData.TargetData);

	
	const AZEROCharacter* Villan = Cast<	AZEROCharacter>(EventData.Target);
	if (Villan && GetCurrentActivationInfo().ActivationMode == EGameplayAbilityActivationMode::Authority)
	{
		FGameplayCueParameters ImpactParams;
		ImpactParams.Location = Villan->GetActorLocation();

		FGameplayTag TagImpact = FGameplayTag::RequestGameplayTag(FName(GCTagForImpact));

		
			Villan->GetAbilitySystemComponent()->AddGameplayCue(TagImpact, ImpactParams);
			ApplyGameplayEffectToTarget(GetCurrentAbilitySpecHandle(), CurrentActorInfo, CurrentActivationInfo, EventData.TargetData, DamageGameplayEffect, 1);
		
		
	}
}

void UGA_BaseProjectileAndWaitForEvent::ProjectileDestroyed(AActor * DestroyedActor)
{
	Projectile = nullptr;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void UGA_BaseProjectileAndWaitForEvent::OnFinishWait()
{
	Projectile = nullptr;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}
