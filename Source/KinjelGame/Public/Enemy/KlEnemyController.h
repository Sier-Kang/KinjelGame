// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "KlEnemyController.generated.h"

/**
 * 
 */
UCLASS()
class KINJELGAME_API AKlEnemyController : public AAIController
{
	GENERATED_BODY()
	
public:
	AKlEnemyController();

	virtual void Tick(float DeltaTime) override;
	
	/** Possess */
	virtual void Possess(APawn* InPawn) override;

	/** Unpossess */
	virtual void UnPossess() override;

	/**
	* On See Player event, invoked by enemy character
	*/
	void OnSeePlayer();

	/** Loose player */
	void LoosePlayer();

	/** Is player dead */
	bool IsPlayerDead();

	/**
	* Get Player's position
	*/
	FVector GetPlayerLocation() const;

public:
	/**
	* Flag of Lock Player
	*/
	bool IsLockPlayer;

protected:
	virtual void BeginPlay() override;

private:
	/** Player Inst */
	class AKlPlayerCharacter* PlayerCharacter;

	/** Character Inst */
	class AKlEnemyCharacter* EnemyCharacter;

	/** Behavior Tree Comp */
	class UBehaviorTreeComponent* BehaviorComp;

	/** Blackboard Data Comp */
	class UBlackboardComponent* BlackboardComp;
};
