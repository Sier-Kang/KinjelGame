// Fill out your copyright notice in the Description page of Project Settings.

#include "KlEnemyTaskDefence.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy/KlEnemyCharacter.h"
#include "Enemy/KlEnemyController.h"
#include "Data/FKlTypes.h"
#include "TimerManager.h"

void UKlEnemyTaskDefence::OnAnimationTimerDone()
{
	if (EnemyController)
	{
		EnemyController->FinishStateDefence();
	}
}

EBTNodeResult::Type UKlEnemyTaskDefence::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (!InitEnemyElement(OwnerComp)) 
		return EBTNodeResult::Failed;

	EnemyCharacter->StartDefence();

	OwnerComp.GetBlackboardComponent()->SetValueAsBool(IsDefenceFinish.SelectedKeyName, false);
	OwnerComp.GetBlackboardComponent()->SetValueAsObject(PlayerPawn.SelectedKeyName, EnemyController->GetPlayerPawn());

	FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(this, &UKlEnemyTaskDefence::OnAnimationTimerDone);

	EnemyController->GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, 2.f, false);

	return EBTNodeResult::Succeeded;
}

EBTNodeResult::Type UKlEnemyTaskDefence::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (!InitEnemyElement(OwnerComp) || !TimerHandle.IsValid())
		return EBTNodeResult::Aborted;

	EnemyController->GetWorld()->GetTimerManager().ClearTimer(TimerHandle);

	return EBTNodeResult::Aborted;
}
