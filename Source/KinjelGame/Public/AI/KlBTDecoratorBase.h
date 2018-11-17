// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "KlBTDecoratorBase.generated.h"

/**
 * 
 */
UCLASS()
class KINJELGAME_API UKlBTDecoratorBase : public UBTDecorator
{
	GENERATED_BODY()
	
private:
	/**
	* Calculate Raw Condition Value
	*/
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
