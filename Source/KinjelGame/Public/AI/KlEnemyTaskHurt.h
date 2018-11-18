// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/KlEnemyTaskBase.h"
#include "KlEnemyTaskHurt.generated.h"

/**
 * 
 */
UCLASS()
class KINJELGAME_API UKlEnemyTaskHurt : public UKlEnemyTaskBase
{
	GENERATED_BODY()
	
protected:
	/** Delegate event of Animation finished */
	void OnAnimationTimerDone();

protected:
	/**
	 * Blackboard Key Wait time
	 */
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	struct FBlackboardKeySelector WaitTime;

	FTimerHandle TimerHandle;

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
