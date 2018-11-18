// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Data/FKlTypes.h"

#include "KlEnemyCharacter.generated.h"

UCLASS()
class KINJELGAME_API AKlEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AKlEnemyCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/**
	* Update HP Bar's Orientation to player, invoked by Controller
	*/
	void UpdateHPBarRotation(FVector PlayerLocation);

	/**
	* Set max speed 
	* @param Speed New Speed
	*/
	void SetMaxSpeed(float Speed);

	/**
	* Get Idle Animation played time
	* @return Wait time
	*/
	float GetIdleWaitTime();

	/** Play Attack action */
	float PlayAttackAction(EEnemyAttackType AttackType);

	/** Play hurt action */
	float PlayHurtAction();

	/** Start Defense */
	void StartDefence();

	/** Stop Defense */
	void StopDefence();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	/** Weapon slot */
	UPROPERTY(VisibleDefaultsOnly, Category = "Mesh")
	class UChildActorComponent* WeaponSocket;

	/** Shield slot */
	UPROPERTY(VisibleDefaultsOnly, Category = "Mesh")
	class UChildActorComponent* ShieldSocket;

	/**
	 * HP Bar
	 */
	UPROPERTY(EditAnywhere, Category = "Mesh")
	class UWidgetComponent* HPBar;

	/**
	 * Enemy Sensing
	 */
	UPROPERTY(EditAnywhere, Category = "Mesh")
	class UPawnSensingComponent* EnemySense;

private:
	UFUNCTION()
	void OnSeePlayer(APawn* PlayerChar);

private:
	/** AI Controller */
	class AKlEnemyController* EnemyController;

	/** Character Animation Inst */
	class UKlEnemyAnim* EnemyAnimInst;

	/** HPBar Widget */
	TSharedPtr<class SKlEnemyHPWidget> HPBarWidget;

	/** HP */
	float HP;
};
