// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/KlEnemyTaskBase.h"
#include "KlEnemyTaskAttackNormal.generated.h"

/**
 * 
 */
UCLASS()
class KINJELGAME_API UKlEnemyTaskAttackNormal : public UKlEnemyTaskBase
{
	GENERATED_BODY()
	
protected:
	/** Blackboard Key Selector - WaitTime */
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	struct FBlackboardKeySelector WaitTime;
	
private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
