// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/KlEnemyTaskBase.h"
#include "KlEnemyTaskChaseSwitch.generated.h"

/**
 * 
 */
UCLASS()
class KINJELGAME_API UKlEnemyTaskChaseSwitch : public UKlEnemyTaskBase
{
	GENERATED_BODY()
	
protected:
	/** Enemy State in blackboard */
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	struct FBlackboardKeySelector EnemyState;
	
private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
