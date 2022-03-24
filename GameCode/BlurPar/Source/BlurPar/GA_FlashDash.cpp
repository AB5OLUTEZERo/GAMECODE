// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_FlashDash.h"
#include"BlurParCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Abilities/Tasks/AbilityTask_MoveToLocation.h"
#include"DrawDebugHelpers.h"
//#include "AT_PlayMontageAndWaitForEvent.h"
#include "Kismet/GameplayStatics.h"
#include"MyAbilitySystemComponent.h"



UGA_FlashDash::UGA_FlashDash()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;

	AbilityInputID = EGASAbilityInputID::Ability_2;

	FGameplayTag Ability1Tag = FGameplayTag::RequestGameplayTag(FName("Ability.Skill.Attack"));
	AbilityTags.AddTag(Ability1Tag);
	ActivationOwnedTags.AddTag(Ability1Tag);

	ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.Skill")));


	DistanceOfTeleport = 500;
	TimeOfTeleport = 1;
}
void UGA_FlashDash::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo * ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData * TriggerEventData)
{
	Hero = Cast<	ABlurParCharacter>(GetAvatarActorFromActorInfo());

	FVector StartLoc = Hero->GetActorLocation();
	FVector EndLoc;
	//Getting the Direction the player is moving
	if (Hero->GetCharacterMovement()->GetCurrentAcceleration() != FVector(0, 0, 0))
	{

		EndLoc = StartLoc + (Hero->GetCharacterMovement()->GetCurrentAcceleration().GetSafeNormal() * DistanceOfTeleport);
	}
	else
	{
		//if the player is not moving make end point behind him
		EndLoc = StartLoc + (Hero->GetActorForwardVector() * -DistanceOfTeleport);
	}

	//Getting all the Players so the collision check dosent effect them and the player can teleport past them
	TArray<AActor*> _TempArryActors;
	FCollisionQueryParams OueryParams;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABlurParCharacter::StaticClass(), _TempArryActors);
	for (int32 i = 0; i < _TempArryActors.Num(); i++)
	{
		OueryParams.AddIgnoredActor(_TempArryActors[i]);
	}
	FHitResult Hit;
	//do a line trace in the movement direction and checks if it hits somthing if it does set that as the End location of the move to
	if (GetWorld()->LineTraceSingleByChannel(Hit, StartLoc, EndLoc, ECollisionChannel::ECC_WorldStatic, OueryParams))
	{
		EndLoc = Hit.Location;
	}
	//Hero->GetCharacterMovement()->GetCurrentAcceleration().GetSafeNormal()
	//DrawDebugSphere(GetWorld(), (EndLoc), 32, 32, FColor::Blue, false,10);
	FGameplayCueParameters TeleParams;
	TeleParams.Location = Hero->GetActorLocation();


	FGameplayTag TagImpact = FGameplayTag::RequestGameplayTag(FName("GameplayCue.Yatagarasu.FlashDashEnter"));

	//Spawning a Teleporter effect in the players location
	Hero->GetAbilitySystemComponent()->AddGameplayCue(TagImpact, TeleParams);

	if (Hero->GetAbilitySystemComponent() && InvisGameplayEffect)
	{
		FGameplayEffectContextHandle EffectContext = Hero->GetAbilitySystemComponent()->MakeEffectContext();
		EffectContext.AddSourceObject(this);


		FGameplayEffectSpecHandle SpecHandle = Hero->GetAbilitySystemComponent()->MakeOutgoingSpec(InvisGameplayEffect, 1, EffectContext);

		if (SpecHandle.IsValid())
		{
			FActiveGameplayEffectHandle GEHandle = Hero->GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		}
	}


	UAbilityTask_MoveToLocation* TaskM = UAbilityTask_MoveToLocation::MoveToLocation(this, NAME_None, (EndLoc), TimeOfTeleport, nullptr, nullptr);
	TaskM->OnTargetLocationReached.AddDynamic(this, &UGA_FlashDash::LocationReached);
	TaskM->ReadyForActivation();
}

void UGA_FlashDash::LocationReached()
{
	//stoping the Momentum so that the player dose not get flug over
	Hero->GetCharacterMovement()->StopMovementImmediately();
	FGameplayCueParameters TeleParams;
	TeleParams.Location = Hero->GetActorLocation();

	FGameplayTag TagImpact = FGameplayTag::RequestGameplayTag(FName("GameplayCue.Yatagarasu.FlashDashExit"));
	Hero->GetAbilitySystemComponent()->AddGameplayCue(TagImpact, TeleParams);

	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}
