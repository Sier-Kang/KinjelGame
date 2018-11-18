// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/KlEnemyTaskBase.h"
#include "KlEnemyTaskLocaESC.generated.h"

/**
 * 
 */
UCLASS()
class KINJELGAME_API UKlEnemyTaskLocaESC : public UKlEnemyTaskBase
{
	GENERATED_BODY()
	
protected:
	/**
	 * Blackboard Key Destination
	 */
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	struct FBlackboardKeySelector Destination;

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
