// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseChar_BaseGameplayAbility.h"
#include "GA_Hunman_UncrownedKing.generated.h"

/**
 * 
 */
UCLASS()
class ZERO_API UGA_Hunman_UncrownedKing : public UBaseChar_BaseGameplayAbility
{
	GENERATED_BODY()
	
public:

	UGA_Hunman_UncrownedKing();

	/** Actually activate ability, do not call this directly. We'll call it from APAHeroCharacter::ActivateAbilitiesWithTags(). */
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	/** Native function, called if an ability ends normally or abnormally. If bReplicate is set to true, try to replicate the ending to the client/server */
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)override;

	class AZEROCharacter* Hero;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Homing)
		float MaxTimeInState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Homing)
		float RangeMultiply;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TSubclassOf<UGameplayEffect> DamageGameplayEffect;

protected:


	UFUNCTION()
		void InputPressedRecived(float TimePressed);

	UFUNCTION()
		void WaitOver();

	UFUNCTION()
		void DoTheDamage(float TimeInState);
};
