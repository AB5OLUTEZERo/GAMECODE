// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_Yatagarasu_SunSlash.h"
#include"ZEROCharacter.h"
#include"DrawDebugHelpers.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "AbilitySystemBlueprintLibrary.h"


UGA_Yatagarasu_SunSlash::UGA_Yatagarasu_SunSlash()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;

	AbilityInputID = EGASAbilityInputID::Ability_1;

	FGameplayTag Ability1Tag = FGameplayTag::RequestGameplayTag(FName("Ability.Skill.Attack"));
	AbilityTags.AddTag(Ability1Tag);
	ActivationOwnedTags.AddTag(Ability1Tag);

	ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.Skill")));
}
void UGA_Yatagarasu_SunSlash::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo * ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData * TriggerEventData)
{
	if (CheckCooldown(Handle, ActorInfo))
	{

		//playing a animation and waiting for a event so we can spawn a projectile
		Hero = Cast<	AZEROCharacter>(GetAvatarActorFromActorInfo());
		if (Hero)
		{
			CommitAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo);
			FString MeleeStartSection = "Cast";
			
			UAnimMontage* MontageToPlay = AttackMontage;
			Task = UAT_PlayMontageAndWaitForEvent::PlayMontageAndWaitForEvent(this, NAME_None, MontageToPlay, FGameplayTagContainer(), 1.0f, FName(*MeleeStartSection), false, 1.0f);
			Task->OnBlendOut.AddDynamic(this, &UGA_Yatagarasu_SunSlash::OnCompletedOrOnCancelled);
			Task->OnCompleted.AddDynamic(this, &UGA_Yatagarasu_SunSlash::OnCompletedOrOnCancelled);
			Task->OnInterrupted.AddDynamic(this, &UGA_Yatagarasu_SunSlash::OnCompletedOrOnCancelled);
			Task->OnCancelled.AddDynamic(this, &UGA_Yatagarasu_SunSlash::OnCompletedOrOnCancelled);
			Task->EventReceived.AddDynamic(this, &UGA_Yatagarasu_SunSlash::EventReceived);
			// ReadyForActivation() is how you activate the AbilityTask in C++. Blueprint has magic from K2Node_LatentGameplayTaskCall that will automatically call ReadyForActivation().
			Task->ReadyForActivation();
		}
		else
		{
			EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Orange, "In Cool Down");
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
	}
}

void UGA_Yatagarasu_SunSlash::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo * ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	if (Task->IsActive())
	{
		Task->EndTask();
	}
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UGA_Yatagarasu_SunSlash::OnCompletedOrOnCancelled(FGameplayTag EventTag, FGameplayEventData EventData)
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
}

void UGA_Yatagarasu_SunSlash::EventReceived(FGameplayTag EventTag, FGameplayEventData EventData)
{
	//if we get the event we spawn a projectile
	if (ProjectileClass)
	{
		
		FString MuzzleLocationName = "Muzzle_02";
		FVector CameraLocation = Hero->GetMesh()->GetSocketLocation(FName(*MuzzleLocationName));;
		FRotator CameraRotation = Hero->GetActorRotation();
	

		
		// Transform MuzzleOffset from camera space to world space.
		FVector MuzzleLocation = CameraLocation + (Hero->GetActorForwardVector() * 100);

		
		FRotator MuzzleRotation = CameraRotation;
		

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
					Projectile = World->SpawnActor<AYatagarasu_SunSlashActor>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
					Projectile->SetOwner(GetAvatarActorFromActorInfo());

					//CommitAbilityCooldown(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true);
					if (Projectile)
					{


						// Set the projectile's initial trajectory.
						FVector LaunchDirection = MuzzleRotation.Vector();
						Projectile->FireInDirection(LaunchDirection);

						//binding afunction to the event on destroyed to stop the gameplay ability  :Instead of this we can use a waitDelay Task but i prefer doing it this way
						Projectile->OnDestroyed.AddDynamic(this, &UGA_Yatagarasu_SunSlash::ProjectileDestroyed);

						//binding a function to on overlap so we will get all the objects overlaped by the projectile
						Projectile->CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &UGA_Yatagarasu_SunSlash::SlashOnOverlapBegin);


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
}

void UGA_Yatagarasu_SunSlash::SlashOnOverlapBegin(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	//checking if the projectile overlapped itself or the owner
	if (OtherActor != Projectile && OtherActor != Hero)
	{
		const AZEROCharacter* Villan = Cast<	AZEROCharacter>(OtherActor);
		if (Villan)
		{
			if (Hero->TeamID != Villan->TeamID)
			{
				//Applying the effects only if they are of type ZEROCharacter effect is for damage and FX
				FGameplayAbilityTargetDataHandle TDataHandle = UAbilitySystemBlueprintLibrary::AbilityTargetDataFromActor(OtherActor);
				ApplyGameplayEffectToTarget(GetCurrentAbilitySpecHandle(), CurrentActorInfo, CurrentActivationInfo, TDataHandle, DamageGameplayEffect, 1);
				ApplyGameplayEffectToTarget(GetCurrentAbilitySpecHandle(), CurrentActorInfo, CurrentActivationInfo, TDataHandle, CueGameplayEffect, 1);
			}
		}
	}
}

void UGA_Yatagarasu_SunSlash::ProjectileDestroyed(AActor * DestroyedActor)
{
	Projectile = nullptr;

	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
}
