// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/KlEnemyTaskBase.h"
#include "KlEnemyTaskDefence.generated.h"

/**
 * 
 */
UCLASS()
class KINJELGAME_API UKlEnemyTaskDefence : public UKlEnemyTaskBase
{
	GENERATED_BODY()
	
protected:
	/** Delegate event */
	void OnAnimationTimerDone();

protected:
	/**
	 * Blackboard Key IsDefenceFinish
	 */
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	struct FBlackboardKeySelector IsDefenceFinish;

	/**
	 * Blackboard Key PlayerPawn
	 */
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector PlayerPawn;

	/** Delegate event of attack action finished */
	FTimerHandle TimerHandle;

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
