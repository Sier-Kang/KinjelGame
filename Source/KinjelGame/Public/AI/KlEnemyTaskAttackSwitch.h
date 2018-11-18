// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/KlEnemyTaskBase.h"
#include "KlEnemyTaskAttackSwitch.generated.h"

/**
 * 
 */
UCLASS()
class KINJELGAME_API UKlEnemyTaskAttackSwitch : public UKlEnemyTaskBase
{
	GENERATED_BODY()
	
protected:
	/**
	 * BlackboardKey AttackType
	 */
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	struct FBlackboardKeySelector AttackType;

	/**
	 * BlackboardboardKey EnemyState
	 */
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector EnemyState;

	/**
	 * BlackboardKey PlayerPawn
	 */
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector PlayerPawn;

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
