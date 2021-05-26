// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseChar_BaseGameplayAbility.h"
#include"AT_PlayMontageAndWaitForEvent.h"
#include "GA_Yatagarasu_BigBang.generated.h"

/**
 * 
 */
UCLASS()
class ZERO_API UGA_Yatagarasu_BigBang : public UBaseChar_BaseGameplayAbility
{
	GENERATED_BODY()

public:
	UGA_Yatagarasu_BigBang();
	/** Actually activate ability, do not call this directly. We'll call it from APAHeroCharacter::ActivateAbilitiesWithTags(). */
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	/** Native function, called if an ability ends normally or abnormally. If bReplicate is set to true, try to replicate the ending to the client/server */
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)override;

	class AZEROCharacter* Hero;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		UAnimMontage* AttackMontage;

	UAT_PlayMontageAndWaitForEvent* Task;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TSubclassOf<UGameplayEffect> DamageGameplayEffect;



	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		float Range;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		float KnockBackStrength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		FString GCTagForBlast;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		FString GCTagForBlastHit;

protected:

	UFUNCTION()
		void OnCompletedOrOnCancelled(FGameplayTag EventTag, FGameplayEventData EventData);

	UFUNCTION()
		void EventReceived(FGameplayTag EventTag, FGameplayEventData EventData);

	
};
