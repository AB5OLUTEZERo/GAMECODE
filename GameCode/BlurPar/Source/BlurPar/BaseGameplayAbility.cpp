// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGameplayAbility.h"



UBaseGameplayAbility::UBaseGameplayAbility()
{
	ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Player.Debuff.Stun")));
}
