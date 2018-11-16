// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BlackboardData.h"
#include "KlEnemyBlackboard.generated.h"

/**
 * 
 */
UCLASS()
class KINJELGAME_API UKlEnemyBlackboard : public UBlackboardData
{
	GENERATED_BODY()
	
public:
	virtual void PostLoad() override;
};
