// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/KlEnemyTaskBase.h"
#include "KlEnemyTaskRotate.generated.h"

/**
 * 
 */
UCLASS()
class KINJELGAME_API UKlEnemyTaskRotate : public UKlEnemyTaskBase
{
	GENERATED_BODY()
	
private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
