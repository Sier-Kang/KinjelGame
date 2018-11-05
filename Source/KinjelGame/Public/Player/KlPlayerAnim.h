// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Data/FKlTypes.h"

#include "KlPlayerAnim.generated.h"

class UAnimMontage;

/**
 * 
 */
UCLASS()
class KINJELGAME_API UKlPlayerAnim : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UKlPlayerAnim();

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	/**
	* Open/Close detection through its overlap event
	*/
	UFUNCTION(BlueprintCallable, Category = "Kinjel")
	void ChangeDetection(bool IsOpen);
public:
	/**
	 * Character's speed
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayAnim")
	float Speed;

	/**
	* Character's rotation
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayAnim")
	FRotator SpineRotator;

protected:
	/** 
	* Initialize Player Character.
	*/
	void InitPlayerCharacter();

	/**
	* Update Anim property variables
	*/
	virtual void UpdateParameters();

	/**
	* Update action with play montage
	*/
	void UpdateMontage();

	/**
	* Allowed view change
	*/
	void AllowViewChange(bool IsAllowed);
protected:
	/** Anim owner character */
	class AKlPlayerCharacter* PlayerCharacter;

	/** Montage resources */
	UAnimMontage* PlayerHitMontage;

	UAnimMontage* PlayerFightMontage;

	UAnimMontage* PlayerPunchMontage;

	UAnimMontage* PlayerEatMontage;

	UAnimMontage* PlayerPickUpMontage;

	UAnimMontage* CurrentMontage;

	/** Animation View Mode */
	EGameViewMode::Type AnimView;
};
