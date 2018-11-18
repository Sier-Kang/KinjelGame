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

	/** Animation finished */
	void ResetProcess(bool IsFinish);

	/** Is player dead */
	bool IsPlayerDead();

	/** Player go away */
	bool IsPlayerAway();

	/** Get Player Pawn */
	UObject* GetPlayerPawn();

	/**
	* Get Player's position
	*/
	FVector GetPlayerLocation() const;

	/** Update Damage Ratio */
	void UpdateDamageRatio(float HPRatioVal);

	/** Complete hurt state */
	void FinishStateHurt();

	/** Complete defense state */
	void FinishStateDefence();

	/** Enemy dead */
	void EnemyDead();

public:
	/**
	* Flag of Lock Player
	*/
	bool IsLockPlayer;

protected:
	virtual void BeginPlay() override;

private:
	/** Update state parameters */
	void UpdateStatePama();

private:
	/** Player Inst */
	class AKlPlayerCharacter* PlayerCharacter;

	/** Character Inst */
	class AKlEnemyCharacter* EnemyCharacter;

	/** Behavior Tree Comp */
	class UBehaviorTreeComponent* BehaviorComp;

	/** Blackboard Data Comp */
	class UBlackboardComponent* BlackboardComp;

	/**Distance list to current player, every 0.5s save once, 8 counts */
	TArray<float> EPDisList;

	FTimerHandle EPDisHandle;

	/** HP Ratio */
	float HPRatio;

	/**Allow to display hurt state */
	bool IsAllowHurt;

	/**Hurt state timer */
	float HurtTimeCount;
};
