// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "BaseChar_AttributeSet.generated.h"


#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
 	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)
/**
 *
 */
UCLASS()
class ZERO_API UBaseChar_AttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UBaseChar_AttributeSet();
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(BlueprintReadOnly, Category = "Attribute", ReplicatedUsing = OnRep_Health)
		FGameplayAttributeData Health;

	ATTRIBUTE_ACCESSORS(UBaseChar_AttributeSet, Health);

	UFUNCTION()
		virtual void OnRep_Health(const FGameplayAttributeData& OldHealth);



	UPROPERTY(BlueprintReadOnly, Category = "Attribute", ReplicatedUsing = OnRep_MaxHealth)
		FGameplayAttributeData MaxHealth;

	ATTRIBUTE_ACCESSORS(UBaseChar_AttributeSet, MaxHealth);

	UFUNCTION()
		virtual void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth);


	UPROPERTY(BlueprintReadOnly, Category = "Attribute", ReplicatedUsing = OnRep_Stamina)
		FGameplayAttributeData Stamina;

	ATTRIBUTE_ACCESSORS(UBaseChar_AttributeSet, Stamina);

	UFUNCTION()
		virtual void OnRep_Stamina(const FGameplayAttributeData& OldStamina);

	UPROPERTY(BlueprintReadOnly, Category = "Attribute", ReplicatedUsing = OnRep_AttackPower)
		FGameplayAttributeData AttackPower;

	ATTRIBUTE_ACCESSORS(UBaseChar_AttributeSet, AttackPower);

	UFUNCTION()
		virtual void OnRep_AttackPower(const FGameplayAttributeData& OldAttackPower);

protected:
	/** Helper function to proportionally adjust the value of an attribute when it's associated max attribute changes. (i.e. When MaxHealth increases, Health increases by an amount that maintains the same percentage as before) */
	void AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute, const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty);


	
};
