// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseChar_AttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"
#include"BaseChar_AbilitySystemComponent.h"
#include"ZEROCharacter.h"


UBaseChar_AttributeSet::UBaseChar_AttributeSet()
{
	MaximumHealth = 0.0f;
	CurrentHealth = 0.0f;
	HealthRegeneration = 0.0f;
}
void UBaseChar_AttributeSet::PreAttributeChange(const FGameplayAttribute & Attribute, float & NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetMaximumHealthAttribute())
	{
		AdjustAttributeForMaxChange(CurrentHealth, MaximumHealth, NewValue, GetCurrentHealthAttribute());
	}
}

void UBaseChar_AttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData & Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetDamageAttribute())
	{
		// Store a local copy of the amount of Damage done and clear the Damage attribute.
		const float LocalDamageDone = GetDamage();

		SetDamage(0.f);

		if (LocalDamageDone > 0.0f)
		{
			
			// Apply the Health change and then clamp it.
			const float NewHealth = GetCurrentHealth() - LocalDamageDone;
			//FString TheFloatStr = FString::SanitizeFloat(NewHealth);
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, *TheFloatStr);
			SetCurrentHealth(FMath::Clamp(NewHealth, 0.0f, GetMaximumHealth()));
			// TheFloatStr = FString::SanitizeFloat(GetCurrentHealth());
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, *TheFloatStr);
			if (GetCurrentHealth() <= 0)
			{
				AZEROCharacter* AvatarCharacter = Cast<AZEROCharacter>(Data.Target.GetAvatarActor());
				FGameplayEffectContextHandle Context = Data.EffectSpec.GetContext();
				AZEROCharacter* SourceCharacter = Cast<AZEROCharacter>(Context.GetInstigator());
				if (AvatarCharacter && SourceCharacter)
				{
					// Empty function from Character Base that logic can be added to.
					SourceCharacter->HandleKill();
					AvatarCharacter->HandleDeath();
					//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Black, "Dead");
				}
			}
		}
	}

	else if (Data.EvaluatedData.Attribute == GetHealingAttribute())
	{
		// Store a local copy of the amount of Healing done and clear the Healing attribute.
		const float LocalHealingDone = GetHealing();

		SetHealing(0.f);

		if (LocalHealingDone > 0.0f)
		{
			// Apply the Health change and then clamp it.
			const float NewHealth = GetCurrentHealth() + LocalHealingDone;

			SetCurrentHealth(FMath::Clamp(NewHealth, 0.0f, GetMaximumHealth()));
		}
	}

	else if (Data.EvaluatedData.Attribute == GetCurrentHealthAttribute())
	{
		SetCurrentHealth(FMath::Clamp(GetCurrentHealth(), 0.0f, GetMaximumHealth()));
		
		
	}

	else if (Data.EvaluatedData.Attribute == GetHealthRegenerationAttribute())
	{
		SetHealthRegeneration(FMath::Clamp(GetHealthRegeneration(), 0.0f, GetMaximumHealth()));
	}
}

void UBaseChar_AttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UBaseChar_AttributeSet, CurrentHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBaseChar_AttributeSet, MaximumHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBaseChar_AttributeSet, HealthRegeneration, COND_None, REPNOTIFY_Always)
}

void UBaseChar_AttributeSet::AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute, const FGameplayAttributeData& MaxAttribute, const float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty) const
{
	UAbilitySystemComponent* AbilitySystemComponent = GetOwningAbilitySystemComponent();

	const float CurrentMaxValue = MaxAttribute.GetCurrentValue();

	if (!FMath::IsNearlyEqual(CurrentMaxValue, NewMaxValue) && AbilitySystemComponent)
	{
		// Change current value to maintain the Current Value / Maximum Value percentage.
		const float CurrentValue = AffectedAttribute.GetCurrentValue();
		const float NewDelta = (CurrentMaxValue > 0.f) ? (CurrentValue * NewMaxValue / CurrentMaxValue) - CurrentValue : NewMaxValue;

		AbilitySystemComponent->ApplyModToAttributeUnsafe(AffectedAttributeProperty, EGameplayModOp::Additive, NewDelta);
	}
}

void UBaseChar_AttributeSet::OnRep_CurrentHealth(const FGameplayAttributeData & OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseChar_AttributeSet, CurrentHealth, OldValue);
}

void UBaseChar_AttributeSet::OnRep_MaximumHealth(const FGameplayAttributeData & OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseChar_AttributeSet, MaximumHealth, OldValue);
}

void UBaseChar_AttributeSet::OnRep_HealthRegeneration(const FGameplayAttributeData & OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseChar_AttributeSet, HealthRegeneration, OldValue);
}
