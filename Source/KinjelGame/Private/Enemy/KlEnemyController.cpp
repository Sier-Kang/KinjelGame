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
		EnemyCharacter->UpdateHPBarRotation(PlayerCharacter->GetCameraPos());
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

bool AKlEnemyController::IsPlayerAway()
{
	if (!IsLockPlayer || !PlayerCharacter || EPDisList.Num() < 6 || IsPlayerDead()) 
		return false;

	int BiggerNum = 0;
	float LastDis = -1.f;
	for (TArray<float>::TIterator It(EPDisList); It; ++It)
	{
		if (*It > LastDis) BiggerNum += 1;
		LastDis = *It;
	}

	return BiggerNum > 3;
}

UObject* AKlEnemyController::GetPlayerPawn()
{
	return PlayerCharacter;
}

FVector AKlEnemyController::GetPlayerLocation() const
{
	if (PlayerCharacter)
	{
		return PlayerCharacter->GetActorLocation();
	}

	return FVector::ZeroVector;
}

void AKlEnemyController::UpdateDamageRatio(float HPRatioVal)
{
	HPRatio = HPRatioVal;

	if (IsAllowHurt) 
		BlackboardComp->SetValueAsEnum("EnemyState", (uint8)EEnemyAIState::ES_Hurt);

	IsAllowHurt = false;
}

void AKlEnemyController::FinishStateHurt()
{
	if (!IsLockPlayer) 
		IsLockPlayer = true;

	if (HPRatio < 0.2f)
	{
		FRandomStream Stream;
		Stream.GenerateNewSeed();

		int ActionRatio = Stream.RandRange(0, 10);
		if (ActionRatio < 4) {
			BlackboardComp->SetValueAsEnum("EnemyState", (uint8)EEnemyAIState::ES_Defence);
		}
		else
		{
			BlackboardComp->SetValueAsEnum("EnemyState", (uint8)EEnemyAIState::ES_Escape);
		}
	}
	else
	{
		FRandomStream Stream;
		Stream.GenerateNewSeed();

		int ActionRatio = Stream.RandRange(0, 10);
		if (ActionRatio < 4) {
			BlackboardComp->SetValueAsEnum("EnemyState", (uint8)EEnemyAIState::ES_Defence);
		}
		else
		{
			BlackboardComp->SetValueAsEnum("EnemyState", (uint8)EEnemyAIState::ES_Attack);
		}
	}
}

void AKlEnemyController::FinishStateDefence()
{
	ResetProcess(true);

	EnemyCharacter->StopDefence();

	float SEToSP = FVector::Distance(EnemyCharacter->GetActorLocation(), GetPlayerLocation());

	if (PlayerCharacter->IsAttack && SEToSP < 200.f)
	{
		BlackboardComp->SetValueAsEnum("EnemyState", (uint8)EEnemyAIState::ES_Defence);
	}
	else
	{
		if (HPRatio < 0.2f)
		{
			BlackboardComp->SetValueAsEnum("EnemyState", (uint8)EEnemyAIState::ES_Escape);
		}
		else
		{
			BlackboardComp->SetValueAsEnum("EnemyState", (uint8)EEnemyAIState::ES_Attack);
		}
	}

}

void AKlEnemyController::EnemyDead()
{
	if (BehaviorComp) 
		BehaviorComp->StopTree(EBTStopMode::Safe);

	if (EPDisHandle.IsValid()) 
		GetWorld()->GetTimerManager().ClearTimer(EPDisHandle);
}

void AKlEnemyController::BeginPlay()
{
	Super::BeginPlay();

	IsLockPlayer = false;

	// Set reference
	PlayerCharacter = Cast<AKlPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	EnemyCharacter = Cast<AKlEnemyCharacter>(GetPawn());

	IsLockPlayer = false;

	FTimerDelegate EPDisDele = FTimerDelegate::CreateUObject(this, &AKlEnemyController::UpdateStatePama);
	GetWorld()->GetTimerManager().SetTimer(EPDisHandle, EPDisDele, 0.3f, true);

	HPRatio = 1;

	IsAllowHurt = false;
	HurtTimeCount = 0.f;
}

void AKlEnemyController::UpdateStatePama()
{
	if (EPDisList.Num() < 6)
	{
		EPDisList.Push(FVector::Distance(EnemyCharacter->GetActorLocation(), GetPlayerLocation()));
	}
	else
	{
		EPDisList.RemoveAt(0);
		EPDisList.Push(FVector::Distance(EnemyCharacter->GetActorLocation(), GetPlayerLocation()));
	}

	if (HurtTimeCount < 6.f)
	{
		HurtTimeCount += 0.3f;
	}
	else
	{
		HurtTimeCount = 0.f;

		IsAllowHurt = true;
	}
}
