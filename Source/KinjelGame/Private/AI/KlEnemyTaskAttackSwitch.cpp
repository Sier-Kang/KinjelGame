// Fill out your copyright notice in the Description page of Project Settings.

#include "KlEnemyTaskAttackSwitch.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "TimerManager.h"

#include "Enemy/KlEnemyCharacter.h"
#include "Enemy/KlEnemyController.h"
#include "Data/FKlTypes.h"
#include "AI/NavigationSystemBase.h"

EBTNodeResult::Type UKlEnemyTaskAttackSwitch::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (!InitEnemyElement(OwnerComp))
		return EBTNodeResult::Failed;

	OwnerComp.GetBlackboardComponent()->SetValueAsObject(PlayerPawn.SelectedKeyName, EnemyController->GetPlayerPawn());
	if (EnemyController->IsPlayerDead())
	{
		// Loose player and change state to patrol
		EnemyController->LoosePlayer();

		OwnerComp.GetBlackboardComponent()->SetValueAsEnum(EnemyState.SelectedKeyName, (uint8)EEnemyAIState::ES_Patrol);

		return EBTNodeResult::Failed;
	}

	float EPDistance = FVector::Distance(EnemyCharacter->GetActorLocation(), EnemyController->GetPlayerLocation());
	if (EPDistance < 200.f)
	{
		// Normal attack
		OwnerComp.GetBlackboardComponent()->SetValueAsEnum(AttackType.SelectedKeyName, (uint8)EEnemyAttackType::EA_Normal);

		return EBTNodeResult::Succeeded;
	}

	if (EPDistance < 300.f && EnemyController->IsPlayerAway())
	{
		// Pursuit player
		OwnerComp.GetBlackboardComponent()->SetValueAsEnum(AttackType.SelectedKeyName, (uint8)EEnemyAttackType::EA_Pursuit);

		return EBTNodeResult::Succeeded;
	}
	if (EPDistance > 200.f && EPDistance < 300.f)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsEnum(AttackType.SelectedKeyName, (uint8)EEnemyAttackType::EA_Dash);

		return EBTNodeResult::Succeeded;
	}
	if (EPDistance > 300.f)
	{

		OwnerComp.GetBlackboardComponent()->SetValueAsEnum(EnemyState.SelectedKeyName, (uint8)EEnemyAIState::ES_Chase);

		return EBTNodeResult::Failed;
	}

	return EBTNodeResult::Failed;
}
