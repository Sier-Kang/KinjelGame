// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/KlEnemyTaskBase.h"
#include "KlEnemyTaskAttackDash.generated.h"

/**
 * 
 */
UCLASS()
class KINJELGAME_API UKlEnemyTaskAttackDash : public UKlEnemyTaskBase
{
	GENERATED_BODY()
	
protected:
	/** Event after animation played */
	void OnAnimationTimerDone();

protected:
	/** Blackboard Key Selector - WaitTime */
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	struct FBlackboardKeySelector WaitTime;
	
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector Destination;

	/** Delegate event of attack action stop */
	FTimerHandle TimerHandle;

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
