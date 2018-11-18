// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/KlEnemyTaskBase.h"
#include "KlEnemyTaskEscapeSwitch.generated.h"

/**
 * 
 */
UCLASS()
class KINJELGAME_API UKlEnemyTaskEscapeSwitch : public UKlEnemyTaskBase
{
	GENERATED_BODY()
	
protected:
	/**
	 * Blackboard Key Enemy State
	 */
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	struct FBlackboardKeySelector EnemyState;

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
