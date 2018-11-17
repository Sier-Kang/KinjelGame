// Fill out your copyright notice in the Description page of Project Settings.

#include "KlEnemyTaskAttackFollow.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "TimerManager.h"

#include "Enemy/KlEnemyCharacter.h"
#include "Enemy/KlEnemyController.h"
#include "Data/FKlTypes.h"
#include "AI/NavigationSystemBase.h"

EBTNodeResult::Type UKlEnemyTaskAttackFollow::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	if (!InitEnemyElement(OwnerComp)) 
		return EBTNodeResult::Failed;

	const float ChaseRadius = 0.f;

	FVector SPToSE = EnemyController->GetPlayerLocation() - EnemyCharacter->GetActorLocation();


	float EPDistance = SPToSE.Size();
	if (EPDistance > 100.f) 
	{
		SPToSE.Normalize();
		const FVector ChaseOrigin = EnemyController->GetPlayerLocation() - 100.f * SPToSE;
		FVector DesLoc(0.f);

		UNavigationSystem::K2_GetRandomReachablePointInRadius(GetWorld(), ChaseOrigin, DesLoc, ChaseRadius);
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(Destination.SelectedKeyName, DesLoc);
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(Destination.SelectedKeyName, EnemyCharacter->GetActorLocation());
	}

	return EBTNodeResult::Succeeded;
}
