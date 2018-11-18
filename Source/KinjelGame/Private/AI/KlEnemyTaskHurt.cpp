// Fill out your copyright notice in the Description page of Project Settings.

#include "KlEnemyTaskHurt.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy/KlEnemyCharacter.h"
#include "Enemy/KlEnemyController.h"
#include "Data/FKlTypes.h"
#include "TimerManager.h"

void UKlEnemyTaskHurt::OnAnimationTimerDone()
{
	if (EnemyController)
		EnemyController->FinishStateHurt();
}

EBTNodeResult::Type UKlEnemyTaskHurt::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (!InitEnemyElement(OwnerComp)) 
		return EBTNodeResult::Failed;

	float ActionDuration = EnemyCharacter->PlayHurtAction();

	OwnerComp.GetBlackboardComponent()->SetValueAsFloat(WaitTime.SelectedKeyName, ActionDuration);

	FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(this, &UKlEnemyTaskHurt::OnAnimationTimerDone);

	EnemyController->GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, ActionDuration, false);

	return EBTNodeResult::Succeeded;
}

EBTNodeResult::Type UKlEnemyTaskHurt::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (!InitEnemyElement(OwnerComp) || !TimerHandle.IsValid()) 
		return EBTNodeResult::Aborted;

	EnemyController->GetWorld()->GetTimerManager().ClearTimer(TimerHandle);

	return EBTNodeResult::Aborted;
}
