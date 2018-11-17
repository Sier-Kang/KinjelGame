// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/KlEnemyTaskBase.h"
#include "KlEnemyTaskWander.generated.h"

/**
 * 
 */
UCLASS()
class KINJELGAME_API UKlEnemyTaskWander : public UKlEnemyTaskBase
{
	GENERATED_BODY()
	
protected:
	/**
	 * Blackboard Selector
	 */
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	struct FBlackboardKeySelector Destination;

	/**
	* Change Wait Time	
	*/
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector WaitTime;

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
