// Fill out your copyright notice in the Description page of Project Settings.

#include "KlEnemyTaskEscapeSwitch.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy/KlEnemyCharacter.h"
#include "Enemy/KlEnemyController.h"
#include "Data/FKlTypes.h"
#include "TimerManager.h"

EBTNodeResult::Type UKlEnemyTaskEscapeSwitch::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (!InitEnemyElement(OwnerComp)) 
		return EBTNodeResult::Failed;

	float EPDistance = FVector::Distance(EnemyCharacter->GetActorLocation(), EnemyController->GetPlayerLocation());

	if (EPDistance > 1500.f) {

		EnemyController->LoosePlayer();

		OwnerComp.GetBlackboardComponent()->SetValueAsEnum(EnemyState.SelectedKeyName, (uint8)EEnemyAIState::ES_Patrol);
	}

	return EBTNodeResult::Succeeded;
}
