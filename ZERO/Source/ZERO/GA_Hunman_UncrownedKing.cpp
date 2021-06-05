// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_Hunman_UncrownedKing.h"
#include"ZEROCharacter.h"
#include"DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Abilities/Tasks/AbilityTask_WaitInputPress.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Abilities/Tasks/AbilityTask_WaitDelay.h"
#include "AbilitySystemBlueprintLibrary.h"


UGA_Hunman_UncrownedKing::UGA_Hunman_UncrownedKing()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;

	AbilityInputID = EGASAbilityInputID::Ultimate;

	FGameplayTag Ability1Tag = FGameplayTag::RequestGameplayTag(FName("Ability.Skill.Attack"));
	AbilityTags.AddTag(Ability1Tag);
	ActivationOwnedTags.AddTag(Ability1Tag);

	MaxTimeInState = 3;
	RangeMultiply = 300;
}
void UGA_Hunman_UncrownedKing::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo * ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData * TriggerEventData)
{
	Hero = Cast<	AZEROCharacter>(GetAvatarActorFromActorInfo());
	if (Hero)
	{
		//DrawDebugSphere(GetWorld(), Hero->GetActorLocation(), 32, 32, FColor::Red, false, 4);
		Hero->GetCharacterMovement()->MaxWalkSpeed = 0.0f;
		UAbilityTask_WaitInputPress* InputTask = UAbilityTask_WaitInputPress::WaitInputPress(this);
		InputTask->OnPress.AddDynamic(this, &UGA_Hunman_UncrownedKing::InputPressedRecived);
		InputTask->ReadyForActivation();

		UAbilityTask_WaitDelay* WaitTask = UAbilityTask_WaitDelay::WaitDelay(this, MaxTimeInState);
		WaitTask->OnFinish.AddDynamic(this, &UGA_Hunman_UncrownedKing::WaitOver);
		WaitTask->ReadyForActivation();

	}
}

void UGA_Hunman_UncrownedKing::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo * ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	Hero->GetCharacterMovement()->MaxWalkSpeed = 600.0f;
}

void UGA_Hunman_UncrownedKing::InputPressedRecived(float TimePressed)
{
	
	
	DoTheDamage(TimePressed);
}

void UGA_Hunman_UncrownedKing::WaitOver()
{
	//DrawDebugSphere(GetWorld(), Hero->GetActorLocation(), 32, 32, FColor::Green, false, 2);
	DoTheDamage(MaxTimeInState);
}

void UGA_Hunman_UncrownedKing::DoTheDamage(float TimeInState)
{
	TArray < TEnumAsByte < EObjectTypeQuery > > BangObjectTypes;
	//BangObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldDynamic));
	BangObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));

	TArray < AActor* > BangActorsToIgnore;
	BangActorsToIgnore.Add(Hero);

	TArray < AActor* > BangOutActors;

	//getting all the player around the user 
	UKismetSystemLibrary::SphereOverlapActors(GetWorld(), Hero->GetActorLocation(), RangeMultiply*TimeInState, BangObjectTypes, AZEROCharacter::StaticClass(), BangActorsToIgnore, BangOutActors);
	//GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Black, "Activate");
	for (AActor* Target : BangOutActors)
	{
		//checking if the actor is a ZEROCharacter to have a extra layer of check even though the overlap function only returns ZEROCharacters
		AZEROCharacter* ZTarget = Cast<AZEROCharacter>(Target);

		if (ZTarget)
		{
			if (Hero->TeamID != ZTarget->TeamID)
			{
				//Applying gameplay effect
				FGameplayAbilityTargetDataHandle TDataHandle = UAbilitySystemBlueprintLibrary::AbilityTargetDataFromActor(ZTarget);
				ApplyGameplayEffectToTarget(GetCurrentAbilitySpecHandle(), CurrentActorInfo, CurrentActivationInfo, TDataHandle, DamageGameplayEffect, 1);
			}
		}

	}
	DrawDebugSphere(GetWorld(), Hero->GetActorLocation(), RangeMultiply*TimeInState, 32, FColor::Cyan, false, 2);
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}
