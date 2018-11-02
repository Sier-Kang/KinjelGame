// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "KlPlayerAnim.generated.h"

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

protected:
	class AKlPlayerCharacter* PlayerCharacter;
};
