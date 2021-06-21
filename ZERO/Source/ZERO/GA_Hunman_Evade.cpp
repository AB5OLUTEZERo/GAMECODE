// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_Hunman_Evade.h"
#include "ZEROCharacter.h"


UGA_Hunman_Evade::UGA_Hunman_Evade()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;

	AbilityInputID = EGASAbilityInputID::Secondry_Attack;
	FGameplayTag Ability1Tag = FGameplayTag::RequestGameplayTag(FName("Ability.Skill.Attack"));
	AbilityTags.AddTag(Ability1Tag);
	ActivationOwnedTags.AddTag(Ability1Tag);

	ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.Skill")));
	ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Player.State.Dead")));
}
void UGA_Hunman_Evade::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo * ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData * TriggerEventData)
{
	Hero = Cast<	AZEROCharacter>(GetAvatarActorFromActorInfo());
	Hero->LaunchCharacter(FVector(0, 0, 3000), true, true);
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
}
