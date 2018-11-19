// Fill out your copyright notice in the Description page of Project Settings.

#include "KlEnemyTaskChaseSwitch.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy/KlEnemyCharacter.h"
#include "Enemy/KlEnemyController.h"
#include "Data/FKlTypes.h"

EBTNodeResult::Type UKlEnemyTaskChaseSwitch::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (!InitEnemyElement(OwnerComp)) 
		return EBTNodeResult::Failed;

	// Get distance to player
	float EPDistance = FVector::Distance(EnemyCharacter->GetActorLocation(), EnemyController->GetPlayerLocation());

	// If distance > 1500, go back to Patrol state, and set IsLockPlayer to false
	if (EPDistance > 1500.f) {
		EnemyController->LoosePlayer();

		OwnerComp.GetBlackboardComponent()->SetValueAsEnum(EnemyState.SelectedKeyName, (uint8)EEnemyAIState::ES_Patrol);
	}

	return EBTNodeResult::Succeeded;
}
