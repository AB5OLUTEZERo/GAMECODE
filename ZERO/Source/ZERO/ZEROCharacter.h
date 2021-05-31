// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include <GameplayEffectTypes.h>
#include"ZERO.h"
#include "ZEROCharacter.generated.h"

UCLASS(config=Game)
class AZEROCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UBaseChar_AbilitySystemComponent* AbilitySystemComp;

	UPROPERTY()
		class UBaseChar_AttributeSet* AttributeSet;
public:
	AZEROCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;


	virtual class UAbilitySystemComponent* GetAbilitySystemComponent()const override;

	virtual void InitializeAttributes();
	virtual void GiveAbilities();


	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;


	UFUNCTION()
		void HandleHealthChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags);

	UFUNCTION()
		void HandleSpeedChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags);

	UFUNCTION()
		void HandleDeath(float DeltaValue, const struct FGameplayTagContainer& EventTags);


	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "GAS")
		TSubclassOf<class UGameplayEffect> DefaultGameplayEffect;



	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "GAS")
		TArray<TSubclassOf<class UBaseChar_BaseGameplayAbility>> DefaultAbilities;

	UFUNCTION()
		virtual void StunTagChanged(const FGameplayTag CallbackTag, int32 NewCount);


	UPROPERTY(BlueprintReadOnly, Category = "Combo")
		int ComboCount;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Combo")
		int MaxComboCount;

	UFUNCTION()
		void IncrementComboCount();

	ETeamID TeamID;
	
protected:

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

