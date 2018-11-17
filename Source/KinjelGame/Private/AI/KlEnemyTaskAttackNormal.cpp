// Fill out your copyright notice in the Description page of Project Settings.

#include "KlEnemyTaskAttackNormal.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "TimerManager.h"

#include "Enemy/KlEnemyCharacter.h"
#include "Enemy/KlEnemyController.h"
#include "Data/FKlTypes.h"
#include "AI/NavigationSystemBase.h"

EBTNodeResult::Type UKlEnemyTaskAttackNormal::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (!InitEnemyElement(OwnerComp)) 
		return EBTNodeResult::Failed;

	float AttackDuration = EnemyCharacter->PlayAttackAction(EEnemyAttackType::EA_Normal);

	OwnerComp.GetBlackboardComponent()->SetValueAsFloat(WaitTime.SelectedKeyName, AttackDuration);

	return EBTNodeResult::Succeeded;
}
