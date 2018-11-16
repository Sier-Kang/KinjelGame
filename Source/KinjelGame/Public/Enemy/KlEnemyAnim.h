// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/FKlTypes.h"
#include "Animation/AnimInstance.h"

#include "KlEnemyAnim.generated.h"

class UAnimSequence;
class UAnimMontage;

/**
 * 
 */
UCLASS()
class KINJELGAME_API UKlEnemyAnim : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UKlEnemyAnim();

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	/**
	* Set Idle Mode, return animation sequence time
	*/
	float SetIdleType(int NewType);

	/**
	* Play attack montage, return animation total time
	*/
	float PlayAttackAction(EEnemyAttackType AttackType);
	
	/**
	* Play get hurt montage, return animation played time
	*/
	float PlayHurtAction();

	/** Stop all animation sequences */
	void StopAllAction();

	/**
	* Allow detection
	*/
	UFUNCTION(BlueprintCallable, Category = "EnemyAnim")
	void ChangeDetection(bool IsOpen);

public:
	/**
	 * Enemy Speed
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EnemyAnim")
	float Speed;

	/**
	 * Animation Idle Type
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EnemyAnim")
	float IdleType;

	/**
	 * Root bone position
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EnemyAnim")
	FVector RootBonePos;

	/**
	 * Root bone alpha
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EnemyAnim")
	float RootBoneAlpha;

	/**
	 * Defense Flag
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EnemyAnim")
	bool IsDefence;

protected:
	class AKlEnemyCharacter* EnemyCharacter;

	/** Idle action */
	UAnimSequence* AnimIdle_I;

	UAnimSequence* AnimIdle_II;

	UAnimSequence* AnimIdle_III;

	/** Attack montage */
	UAnimMontage* AnimAttack_I;
	UAnimMontage* AnimAttack_II;
	UAnimMontage* AnimAttack_III;
	UAnimMontage* AnimAttack_IV;

	UAnimSequence* AnimAttackSeq_III;
	UAnimSequence* AnimAttackSeq_IV;

	/** Get Hurt montage */
	UAnimMontage* AnimHurt;

	/** Action timer */
	float CurrentPlayTime;

	/** Y Position in first frame of the action */
	float StartYPos;
};
