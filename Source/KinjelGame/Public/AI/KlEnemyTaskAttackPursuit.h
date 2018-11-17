// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/KlEnemyTaskBase.h"
#include "KlEnemyTaskAttackPursuit.generated.h"

/**
 * 
 */
UCLASS()
class KINJELGAME_API UKlEnemyTaskAttackPursuit : public UKlEnemyTaskBase
{
	GENERATED_BODY()

protected:
	void OnAnimationTimerDone();
	
protected:
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	struct FBlackboardKeySelector IsActionFinish;
	
	/** Delegate event of attack action finished */
	FTimerHandle TimerHandle;

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
