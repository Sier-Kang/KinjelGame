// Fill out your copyright notice in the Description page of Project Settings.

#include "KlEnemyController.h"
#include "Player/KlPlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Enemy/KlEnemyCharacter.h"
#include "AI/KlEnemyBlackboard.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

AKlEnemyController::AKlEnemyController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AKlEnemyController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Update enemy's HP Bar's orientation
	if (PlayerCharacter && EnemyCharacter)
	{
		EnemyCharacter->UpdateHPBarRotation(PlayerCharacter->GetActorLocation());
	}
}

void AKlEnemyController::Possess(APawn* InPawn)
{
	// Super invoked
	Super::Possess(InPawn);

	// Initialize Enemy Character
	EnemyCharacter = Cast<AKlEnemyCharacter>(InPawn);

	// Get BehaviorTree 
	UBehaviorTree* StaticBehaviorTreeObject = LoadObject<UBehaviorTree>(NULL, 
		TEXT("BehaviorTree'/Game/Blueprint/Enemy/EnemyBehaviorTree.EnemyBehaviorTree'"));

	// Here Duplicate the resource's reason is that, when put 1 enemy in the scene there is no
	// problem, but 2 or more, you must duplicate it to avoid error.
	UBehaviorTree* BehaviorTreeObject = DuplicateObject<UBehaviorTree>(StaticBehaviorTreeObject, NULL);
	if (!BehaviorTreeObject)
	{
		return;
	}

	BehaviorTreeObject->BlackboardAsset = DuplicateObject<UKlEnemyBlackboard>(
		(UKlEnemyBlackboard*)StaticBehaviorTreeObject->BlackboardAsset, 
		NULL
	);

	BlackboardComp = Blackboard;

	bool IsSuccess = true;

	if (BehaviorTreeObject->BlackboardAsset && (Blackboard == nullptr || Blackboard->IsCompatibleWith(BehaviorTreeObject->BlackboardAsset) == false))
	{
		IsSuccess = UseBlackboard(BehaviorTreeObject->BlackboardAsset, BlackboardComp);
	}

	if (IsSuccess)
	{
		BehaviorComp = Cast<UBehaviorTreeComponent>(BrainComponent);
		if (!BehaviorComp)
		{
			BehaviorComp = NewObject<UBehaviorTreeComponent>(this, TEXT("BehaviorComp"));
			BehaviorComp->RegisterComponent();
		}
		BrainComponent = BehaviorComp;
		check(BehaviorComp != NULL);

		BehaviorComp->StartTree(*BehaviorTreeObject, EBTExecutionMode::Looped);

		// Preset is Patrol
		BlackboardComp->SetValueAsEnum("EnemyState", (uint8)EEnemyAIState::ES_Patrol);

		EnemyCharacter->SetMaxSpeed(100.f);
	}
}

void AKlEnemyController::UnPossess()
{
	Super::UnPossess();

	// Stop Behavior Tree
	if (BehaviorComp)
		BehaviorComp->StopTree();
}

void AKlEnemyController::OnSeePlayer()
{
	if (IsLockPlayer || IsPlayerDead())
		return;

	// Set Lock player
	IsLockPlayer = true;

	BlackboardComp->SetValueAsEnum("EnemyState", (uint8)EEnemyAIState::ES_Chase);

	// Change character's max speed
	EnemyCharacter->SetMaxSpeed(300.f);
}

void AKlEnemyController::LoosePlayer()
{
	IsLockPlayer = false;
}

void AKlEnemyController::ResetProcess(bool IsFinish)
{
	BlackboardComp->SetValueAsBool("ProcessFinish", IsFinish);
}

bool AKlEnemyController::IsPlayerDead()
{
	if (PlayerCharacter)
		return PlayerCharacter->IsPlayerDead();

	return false;
}

FVector AKlEnemyController::GetPlayerLocation() const
{
	if (PlayerCharacter)
	{
		return PlayerCharacter->GetActorLocation();
	}

	return FVector::ZeroVector;
}

void AKlEnemyController::BeginPlay()
{
	Super::BeginPlay();

	IsLockPlayer = false;

	// Set reference
	PlayerCharacter = Cast<AKlPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	EnemyCharacter = Cast<AKlEnemyCharacter>(GetPawn());
}
