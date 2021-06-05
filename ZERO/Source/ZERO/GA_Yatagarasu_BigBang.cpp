// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_Yatagarasu_BigBang.h"
#include"ZEROCharacter.h"
#include"DrawDebugHelpers.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "BaseChar_AbilitySystemComponent.h"


UGA_Yatagarasu_BigBang::UGA_Yatagarasu_BigBang()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;

	AbilityInputID = EGASAbilityInputID::Ultimate;

	FGameplayTag Ability1Tag = FGameplayTag::RequestGameplayTag(FName("Ability.Skill.Attack"));
	AbilityTags.AddTag(Ability1Tag);
	ActivationOwnedTags.AddTag(Ability1Tag);

	Range = 200;
	KnockBackStrength = 2000;
}
void UGA_Yatagarasu_BigBang::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo * ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData * TriggerEventData)
{
	Hero = Cast<	AZEROCharacter>(GetAvatarActorFromActorInfo());
	if (Hero)
	{
		CommitAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo);
		FString MeleeStartSection = "Cast";
		//FName MontageSectionName = FName(*MeleeStartSection);
		UAnimMontage* MontageToPlay = AttackMontage;
		Task = UAT_PlayMontageAndWaitForEvent::PlayMontageAndWaitForEvent(this, NAME_None, MontageToPlay, FGameplayTagContainer(), 1.0f, FName(*MeleeStartSection), false, 1.0f);
		Task->OnBlendOut.AddDynamic(this, &UGA_Yatagarasu_BigBang::OnCompletedOrOnCancelled);
		Task->OnCompleted.AddDynamic(this, &UGA_Yatagarasu_BigBang::OnCompletedOrOnCancelled);
		Task->OnInterrupted.AddDynamic(this, &UGA_Yatagarasu_BigBang::OnCompletedOrOnCancelled);
		Task->OnCancelled.AddDynamic(this, &UGA_Yatagarasu_BigBang::OnCompletedOrOnCancelled);
		Task->EventReceived.AddDynamic(this, &UGA_Yatagarasu_BigBang::EventReceived);
		// ReadyForActivation() is how you activate the AbilityTask in C++. Blueprint has magic from K2Node_LatentGameplayTaskCall that will automatically call ReadyForActivation().
		Task->ReadyForActivation();
	}
	else
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
	}
}

void UGA_Yatagarasu_BigBang::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo * ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	if (Task->IsActive())
	{
		Task->EndTask();
	}
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UGA_Yatagarasu_BigBang::OnCompletedOrOnCancelled(FGameplayTag EventTag, FGameplayEventData EventData)
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
}

void UGA_Yatagarasu_BigBang::EventReceived(FGameplayTag EventTag, FGameplayEventData EventData)
{
	FGameplayCueParameters ImpactParams;
	ImpactParams.Location = Hero->GetActorLocation();
	FGameplayTag TagImpact = FGameplayTag::RequestGameplayTag(FName(GCTagForBlast));
	Hero->GetAbilitySystemComponent()->AddGameplayCue(TagImpact, ImpactParams);

	TArray < TEnumAsByte < EObjectTypeQuery > > BangObjectTypes;
	//BangObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldDynamic));
	BangObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));

	TArray < AActor* > BangActorsToIgnore;
	BangActorsToIgnore.Add(Hero);

	TArray < AActor* > BangOutActors;

	//getting all the player around the user 
	UKismetSystemLibrary::SphereOverlapActors(GetWorld(), Hero->GetActorLocation(), Range, BangObjectTypes,AZEROCharacter::StaticClass(), BangActorsToIgnore, BangOutActors);
	//GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Black, "Activate");
	for (AActor* Target : BangOutActors)
	{
		//checking if the actor is a ZEROCharacter to have a extra layer of check even though the overlap function only returns ZEROCharacters
		AZEROCharacter* ZTarget = Cast<AZEROCharacter>(Target);
		
		if (ZTarget)
		{
			if (Hero->TeamID != ZTarget->TeamID)
			{
				FVector KnockBackDir = ((ZTarget->GetActorLocation()) - (Hero->GetActorLocation())).GetSafeNormal() * KnockBackStrength;
				KnockBackDir.Z += 20;
				//Adding a knock back
				ZTarget->LaunchCharacter(KnockBackDir, true, true);

				//Applying gameplay effect
				FGameplayAbilityTargetDataHandle TDataHandle = UAbilitySystemBlueprintLibrary::AbilityTargetDataFromActor(ZTarget);
				ApplyGameplayEffectToTarget(GetCurrentAbilitySpecHandle(), CurrentActorInfo, CurrentActivationInfo, TDataHandle, DamageGameplayEffect, 1);


				//Applying FX
				FGameplayCueParameters HitImpactParams;
				HitImpactParams.Location = ZTarget->GetActorLocation();
				FGameplayTag TagHitImpact = FGameplayTag::RequestGameplayTag(FName(GCTagForBlastHit));
				ZTarget->GetAbilitySystemComponent()->AddGameplayCue(TagHitImpact, HitImpactParams);
			}
		}

	}

	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}
