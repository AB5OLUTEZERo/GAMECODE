// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_BaseTeamBuff.h"
#include"ZEROCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "AbilitySystemBlueprintLibrary.h"


UGA_BaseTeamBuff::UGA_BaseTeamBuff()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;

	AbilityInputID = EGASAbilityInputID::Ability_2;

	ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Player.Debuff.Stun")));
}
void UGA_BaseTeamBuff::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo * ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData * TriggerEventData)
{
	Hero = Cast<	AZEROCharacter>(GetAvatarActorFromActorInfo());
	if (Hero)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, "RepFire");
		TArray<AActor*> _TempArryActors;
		ETeamID TID;
		if (bIsForTeam)
		{
			TID = Hero->TeamID;
		}
		else
		{
			TID = ETeamID::TeamA;
			if (Hero->TeamID == ETeamID::TeamA)
			{
				TID = ETeamID::TeamB;
			}

		}

		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AZEROCharacter::StaticClass(), _TempArryActors);
		for (int32 i = 0; i < _TempArryActors.Num(); i++)
		{
			AZEROCharacter* ZeroChar = Cast<AZEROCharacter>(_TempArryActors[i]);
			if (ZeroChar->TeamID == TID)
			{
				FGameplayAbilityTargetDataHandle TDataHandle = UAbilitySystemBlueprintLibrary::AbilityTargetDataFromActor(ZeroChar);
				ApplyGameplayEffectToTarget(GetCurrentAbilitySpecHandle(), CurrentActorInfo, CurrentActivationInfo, TDataHandle, BuffOrDeBuffGameplayEffect, 1);

			}
		}
	}
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void UGA_BaseTeamBuff::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo * ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

}
