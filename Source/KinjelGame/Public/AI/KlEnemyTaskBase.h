// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "KlEnemyTaskBase.generated.h"

/**
 * 
 */
UCLASS()
class KINJELGAME_API UKlEnemyTaskBase : public UBTTaskNode
{
	GENERATED_BODY()
	
protected:
	/**
	* Initialize controller and character
	* @param OwnerComp
	* @return initialize success or not
	*/
	bool InitEnemyElement(UBehaviorTreeComponent& OwnerComp);

protected:
	class AKlEnemyController* EnemyController;

	class AKlEnemyCharacter* EnemyCharacter;
};