// Fill out your copyright notice in the Description page of Project Settings.

#include "KlEnemyTaskRotate.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy/KlEnemyCharacter.h"
#include "Enemy/KlEnemyController.h"
#include "Data/FKlTypes.h"
#include "TimerManager.h"
#include "AI/NavigationSystemBase.h"

EBTNodeResult::Type UKlEnemyTaskRotate::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (!InitEnemyElement(OwnerComp)) 
		return EBTNodeResult::Failed;

	return EBTNodeResult::Succeeded;
}
