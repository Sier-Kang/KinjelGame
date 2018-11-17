// Fill out your copyright notice in the Description page of Project Settings.

#include "KlEnemyTaskLocaSP.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy/KlEnemyCharacter.h"
#include "Enemy/KlEnemyController.h"
#include "Data/FKlTypes.h"
#include "AI/NavigationSystemBase.h"

EBTNodeResult::Type UKlEnemyTaskLocaSP::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	if (!InitEnemyElement(OwnerComp)) 
		return EBTNodeResult::Failed;

	const float ChaseRadius = 20.f;
	// Get normalize vector between enemy and player
	FVector SPToSE = EnemyController->GetPlayerLocation() - EnemyCharacter->GetActorLocation();
	SPToSE.Normalize();

	const FVector ChaseOrigin = EnemyController->GetPlayerLocation() - 100.f * SPToSE;

	FVector DesLoc(0.f);

	UNavigationSystem::K2_GetRandomReachablePointInRadius(GetWorld(), ChaseOrigin, DesLoc, ChaseRadius);

	OwnerComp.GetBlackboardComponent()->SetValueAsVector(Destination.SelectedKeyName, DesLoc);

	EnemyCharacter->SetMaxSpeed(300.f);

	return EBTNodeResult::Succeeded;
}
