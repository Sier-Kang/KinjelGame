// Fill out your copyright notice in the Description page of Project Settings.

#include "KlEnemyTaskAttackPursuit.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "TimerManager.h"

#include "Enemy/KlEnemyCharacter.h"
#include "Enemy/KlEnemyController.h"
#include "Data/FKlTypes.h"
#include "AI/NavigationSystemBase.h"

void UKlEnemyTaskAttackPursuit::OnAnimationTimerDone()
{
	if (EnemyController) EnemyController->ResetProcess(true);

	if (EnemyCharacter) EnemyCharacter->SetMaxSpeed(300.f);
}

EBTNodeResult::Type UKlEnemyTaskAttackPursuit::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (!InitEnemyElement(OwnerComp)) 
		return EBTNodeResult::Failed;

	float AttackDuration = EnemyCharacter->PlayAttackAction(EEnemyAttackType::EA_Pursuit);

	EnemyCharacter->SetMaxSpeed(600.f);
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(IsActionFinish.SelectedKeyName, false);

	FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(this, &UKlEnemyTaskAttackPursuit::OnAnimationTimerDone);
	EnemyController->GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, AttackDuration, false);

	return EBTNodeResult::Succeeded;
}

EBTNodeResult::Type UKlEnemyTaskAttackPursuit::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	if (!InitEnemyElement(OwnerComp) || !TimerHandle.IsValid()) 
		return EBTNodeResult::Aborted;

	EnemyController->GetWorld()->GetTimerManager().ClearTimer(TimerHandle);

	return EBTNodeResult::Aborted;
}
