// Fill out your copyright notice in the Description page of Project Settings.

#include "KlEnemyTaskBase.h"
#include "KlEnemyCharacter.h"
#include "KlEnemyController.h"

bool UKlEnemyTaskBase::InitEnemyElement(UBehaviorTreeComponent& OwnerComp)
{
	// If already initialized, return immediately
	if (EnemyController && EnemyCharacter)
	{
		return true;
	}

	EnemyController = Cast<AKlEnemyController>(OwnerComp.GetAIOwner());
	if (EnemyController)
	{
		EnemyCharacter = Cast<AKlEnemyCharacter>(EnemyController->GetPawn());

		if (EnemyCharacter)
			return true;
	}

	return false;
}
