// Fill out your copyright notice in the Description page of Project Settings.

#include "KlEnemyTaskLocaESC.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy/KlEnemyCharacter.h"
#include "Enemy/KlEnemyController.h"
#include "Data/FKlTypes.h"
#include "TimerManager.h"
#include "AI/NavigationSystemBase.h"

EBTNodeResult::Type UKlEnemyTaskLocaESC::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (!InitEnemyElement(OwnerComp)) 
		return EBTNodeResult::Failed;

	const float ChaseRadius = 2000.f;

	FVector SPToSE = EnemyCharacter->GetActorLocation() - EnemyController->GetPlayerLocation();

	const FVector ChaseOrigin = EnemyCharacter->GetActorLocation();

	FVector DesLoc(0.f);

	UNavigationSystem::K2_GetRandomReachablePointInRadius(GetWorld(), ChaseOrigin, DesLoc, ChaseRadius);

	while (FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(SPToSE, DesLoc - EnemyCharacter->GetActorLocation()))) > 90.f)
	{
		UNavigationSystem::K2_GetRandomReachablePointInRadius(GetWorld(), ChaseOrigin, DesLoc, ChaseRadius);
	}

	EnemyCharacter->SetMaxSpeed(300.f);
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(Destination.SelectedKeyName, DesLoc);

	return EBTNodeResult::Succeeded;
}
