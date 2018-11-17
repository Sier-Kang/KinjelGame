// Fill out your copyright notice in the Description page of Project Settings.

#include "KlEnemyBlackboard.h"
#include "Data/FKlTypes.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Enum.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Float.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "KlPlayerCharacter.h"

void UKlEnemyBlackboard::PostLoad()
{
	Super::PostLoad();

	// Destination
	FBlackboardEntry Destination;
	Destination.EntryName = FName("Destination");
	UBlackboardKeyType_Vector* DestinationKeyType = NewObject<UBlackboardKeyType_Vector>();
	Destination.KeyType = DestinationKeyType;

	// Enemy State
	FBlackboardEntry EnemyState;
	EnemyState.EntryName = FName("EnemyState");
	UBlackboardKeyType_Enum* EnemyStateKeyType = NewObject<UBlackboardKeyType_Enum>();
	//EnemyStateKeyType->EnumType = FindObject<UEnum>(ANY_PACKAGE, *FString("EEnemyAIState"), true);
	EnemyStateKeyType->EnumName = FString("EEnemyAIState");
	EnemyState.KeyType = EnemyStateKeyType;

	// Wait Time
	FBlackboardEntry WaitTime;
	WaitTime.EntryName = FName("WaitTime");
	WaitTime.KeyType = NewObject<UBlackboardKeyType_Float>();

	// Attack Type
	FBlackboardEntry AttackType;
	AttackType.EntryName = FName("AttackType");
	UBlackboardKeyType_Enum* AttackTypeKeyType = NewObject<UBlackboardKeyType_Enum>();
	//AttackTypeKeyType->EnumType = FindObject<UEnum>(ANY_PACKAGE, *FString("EEnemyAttackType"), true);
	AttackTypeKeyType->EnumName = FString("EEnemyAttackType");
	AttackType.KeyType = AttackTypeKeyType;

	// Player Ref
	FBlackboardEntry PlayerPawn;
	PlayerPawn.EntryName = FName("PlayerPawn");
	UBlackboardKeyType_Object* PlayerPawnKeyType = NewObject<UBlackboardKeyType_Object>();
	PlayerPawnKeyType->BaseClass = AKlPlayerCharacter::StaticClass();
	PlayerPawn.KeyType = PlayerPawnKeyType;

	// If Action Finish
	FBlackboardEntry ProcessFinish;
	ProcessFinish.EntryName = FName("ProcessFinish");
	ProcessFinish.KeyType = NewObject<UBlackboardKeyType_Bool>();

	Keys.Add(Destination);
	Keys.Add(EnemyState);
	Keys.Add(WaitTime);
	Keys.Add(AttackType);
	Keys.Add(PlayerPawn);
	Keys.Add(ProcessFinish);
}
