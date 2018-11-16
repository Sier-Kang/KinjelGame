// Fill out your copyright notice in the Description page of Project Settings.

#include "KlEnemyBlackboard.h"
#include "Data/FKlTypes.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Enum.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Float.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"

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

	Keys.Add(Destination);
	Keys.Add(EnemyState);
}
