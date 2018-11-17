// Fill out your copyright notice in the Description page of Project Settings.

#include "KlEnemyTaskWander.h"
#include "Enemy/KlEnemyCharacter.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"

EBTNodeResult::Type UKlEnemyTaskWander::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Initialize Enemy Element
	if (!InitEnemyElement(OwnerComp))
		return EBTNodeResult::Failed;

	const float WanderRadius = 1000.f;

	// Start point is its current position
	const FVector WanderOrigin = EnemyCharacter->GetActorLocation();

	// Random destination
	FVector DesLoc(0.f);

	// Use Navigation System to get random position
	UNavigationSystem::K2_GetRandomReachablePointInRadius(GetWorld(), WanderOrigin, DesLoc, WanderRadius);

	// If distance between them < 500 m, repeat this.
	if (FVector::Distance(WanderOrigin, DesLoc) < 500.f) {
		UNavigationSystem::K2_GetRandomReachablePointInRadius(GetWorld(), WanderOrigin, DesLoc, WanderRadius);
	}

	EnemyCharacter->SetMaxSpeed(100.f);

	OwnerComp.GetBlackboardComponent()->SetValueAsVector(Destination.SelectedKeyName, DesLoc);

	float TotalWaitTime = EnemyCharacter->GetIdleWaitTime();

	OwnerComp.GetBlackboardComponent()->SetValueAsFloat(WaitTime.SelectedKeyName, TotalWaitTime);

	return EBTNodeResult::Succeeded;
}
