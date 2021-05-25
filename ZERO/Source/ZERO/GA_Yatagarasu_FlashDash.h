// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseChar_BaseGameplayAbility.h"
#include "GA_Yatagarasu_FlashDash.generated.h"

/**
 * 
 */
UCLASS()
class ZERO_API UGA_Yatagarasu_FlashDash : public UBaseChar_BaseGameplayAbility
{
	GENERATED_BODY()
	

public:
	UGA_Yatagarasu_FlashDash();


	/** Actually activate ability, do not call this directly. We'll call it from APAHeroCharacter::ActivateAbilitiesWithTags(). */
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	class AZEROCharacter* Hero;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		UAnimMontage* DashMontage;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TSubclassOf<UGameplayEffect> InvisGameplayEffect;
protected:


	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Combo")
		float DistanceOfTeleport;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Combo")
		float TimeOfTeleport;

	UFUNCTION()
		void LocationReached();


};
