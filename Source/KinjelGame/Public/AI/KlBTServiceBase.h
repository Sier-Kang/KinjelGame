// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "KlBTServiceBase.generated.h"

/**
 * 
 */
UCLASS()
class KINJELGAME_API UKlBTServiceBase : public UBTService
{
	GENERATED_BODY()
	
protected:
	/**
	* Tick Node
	*/
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
