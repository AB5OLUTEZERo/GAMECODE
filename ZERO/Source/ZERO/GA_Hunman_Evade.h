// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseChar_BaseGameplayAbility.h"
#include "GA_Hunman_Evade.generated.h"

/**
 * 
 */
UCLASS()
class ZERO_API UGA_Hunman_Evade : public UBaseChar_BaseGameplayAbility
{
	GENERATED_BODY()

public:
	UGA_Hunman_Evade();
	/** Actually activate ability, do not call this directly. We'll call it from APAHeroCharacter::ActivateAbilitiesWithTags(). */
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	class AZEROCharacter* Hero;
	
};
