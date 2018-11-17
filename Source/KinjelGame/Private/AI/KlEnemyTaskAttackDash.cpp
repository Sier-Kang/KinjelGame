// Fill out your copyright notice in the Description page of Project Settings.

#include "KlEnemyTaskAttackDash.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "TimerManager.h"

#include "Enemy/KlEnemyCharacter.h"
#include "Enemy/KlEnemyController.h"
#include "Data/FKlTypes.h"
#include "AI/NavigationSystemBase.h"

void UKlEnemyTaskAttackDash::OnAnimationTimerDone()
{
	if (EnemyCharacter) EnemyCharacter->SetMaxSpeed(300.f);
}

EBTNodeResult::Type UKlEnemyTaskAttackDash::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (!InitEnemyElement(OwnerComp)) 
		return EBTNodeResult::Failed;

	float AttackDuration = EnemyCharacter->PlayAttackAction(EEnemyAttackType::EA_Dash);

	const float ChaseRadius = 5.f;
	FVector SPToSE = EnemyController->GetPlayerLocation() - EnemyCharacter->GetActorLocation();
	SPToSE.Normalize();

	const FVector ChaseOrigin = EnemyController->GetPlayerLocation() - 20.f * SPToSE;

	FVector DesLoc(0.f);
	UNavigationSystem::K2_GetRandomReachablePointInRadius(GetWorld(), ChaseOrigin, DesLoc, ChaseRadius);

	float Speed = (FVector::Distance(EnemyCharacter->GetActorLocation(), DesLoc)) / AttackDuration + 30.f;
	EnemyCharacter->SetMaxSpeed(Speed);

	OwnerComp.GetBlackboardComponent()->SetValueAsVector(Destination.SelectedKeyName, DesLoc);
	OwnerComp.GetBlackboardComponent()->SetValueAsFloat(WaitTime.SelectedKeyName, AttackDuration);

	FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(this, &UKlEnemyTaskAttackDash::OnAnimationTimerDone);
	EnemyController->GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, AttackDuration, false);
	
	return EBTNodeResult::Succeeded;
}

EBTNodeResult::Type UKlEnemyTaskAttackDash::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (!InitEnemyElement(OwnerComp) || !TimerHandle.IsValid()) 
		return EBTNodeResult::Aborted;

	EnemyController->GetWorld()->GetTimerManager().ClearTimer(TimerHandle);

	return EBTNodeResult::Aborted;
}
