// Fill out your copyright notice in the Description page of Project Settings.

#include "KlEnemyCharacter.h"
#include "Enemy/KlEnemyController.h"
#include "Components/CapsuleComponent.h"
#include "ConstructorHelpers.h"
#include "Engine/SkeletalMesh.h"
#include "Animation/AnimInstance.h"
#include "Components/ChildActorComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnemyTool/KlEnemyTool.h"
#include "UI/Widgets/SKlEnemyHPWidget.h"
#include "Components/WidgetComponent.h"
#include "KlPlayerCharacter.h"
#include "Enemy/KlEnemyAnim.h"
#include "Enemy/KlEnemyController.h"
#include "Perception/PawnSensingComponent.h"
#include "FKlHelper.h"
#include "Data/FKlDataHandle.h"
#include "KlFlobObject.h"
#include "Data/FKlTypes.h"

// Sets default values
AKlEnemyCharacter::AKlEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Bind AI Controller
	AIControllerClass = AKlEnemyController::StaticClass();

	// Collision settings
	GetCapsuleComponent()->SetCollisionProfileName(FName("EnemyProfile"));
	GetCapsuleComponent()->SetGenerateOverlapEvents(true);

	// Add Skeletal Mesh
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> StaticEnemyMesh(
		TEXT("SkeletalMesh'/Game/Res/PolygonAdventure/Mannequin/Enemy/SkMesh/Enemy.Enemy'")
	);
	GetMesh()->SetSkeletalMesh(StaticEnemyMesh.Object);
	GetMesh()->SetCollisionObjectType(ECC_Pawn);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetCollisionResponseToAllChannels(ECR_Ignore);
	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -95.f));
	GetMesh()->SetRelativeRotation(FQuat::MakeFromEuler(FVector(0.f, 0.f, -90.f)));

	// Add Skeletal Mesh Animation
	static ConstructorHelpers::FClassFinder<UAnimInstance> StaticEnemyAnim(
		TEXT("AnimBlueprint'/Game/Blueprint/Enemy/Enemy_Anim.Enemy_Anim_C'")
	);
	GetMesh()->AnimClass = StaticEnemyAnim.Class;


	// Initialize socket
	WeaponSocket = CreateDefaultSubobject<UChildActorComponent>(TEXT("WeaponSocket"));

	ShieldSocket = CreateDefaultSubobject<UChildActorComponent>(TEXT("SheildSocket"));

	// Set HP Bar Widget
	HPBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBar"));
	HPBar->SetupAttachment(RootComponent);

	// Set pawn sensing component
	EnemySense = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("EnemySense"));

	// Add dead asset
	AnimDead_I = Cast<UAnimationAsset>(StaticLoadObject(UAnimationAsset::StaticClass(), 
		NULL, 
		*FString("AnimSequence'/Game/Res/PolygonAdventure/Mannequin/Enemy/Animation/FightGroup/Enemy_Dead_I.Enemy_Dead_I'"))
	);

	AnimDead_II = Cast<UAnimationAsset>(StaticLoadObject(UAnimationAsset::StaticClass(), 
		NULL, 
		*FString("AnimSequence'/Game/Res/PolygonAdventure/Mannequin/Enemy/Animation/FightGroup/Enemy_Dead_II.Enemy_Dead_II'"))
	);

	IsDestroyNextTick = false;
}

// Called when the game starts or when spawned
void AKlEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Get reference
	EnemyController = Cast<AKlEnemyController>(GetController());

	EnemyAnimInst = Cast<UKlEnemyAnim>(GetMesh()->GetAnimInstance());
	
	// Bind enemy tool to skeletal mesh sockets
	WeaponSocket->AttachToComponent(GetMesh(), 
		FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("RHSocket"));

	ShieldSocket->AttachToComponent(GetMesh(), 
		FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("LHSocket"));

	// Add tool to socket
	WeaponSocket->SetChildActorClass(AKlEnemyTool::SpawnEnemyWeapon());
	ShieldSocket->SetChildActorClass(AKlEnemyTool::SpawnEnemyShield());

	// Set HP Bar Slate widget
	SAssignNew(HPBarWidget, SKlEnemyHPWidget);
	HPBar->SetSlateWidget(HPBarWidget);
	HPBar->SetRelativeLocation(FVector(0.f, 0.f, 100.f));
	HPBar->SetDrawSize(FVector2D(100.f, 10.f));

	HP = 200.f;
	HPBarWidget->ChangeHP(HP / 200.f);

	// Set enemy sense component
	EnemySense->HearingThreshold = 0.f;
	EnemySense->LOSHearingThreshold = 0.f;
	EnemySense->SightRadius = 1000.f;
	EnemySense->SetPeripheralVisionAngle(55.f);
	EnemySense->bHearNoises = false;

	FScriptDelegate OnSeePlayerDelegate;
	OnSeePlayerDelegate.BindUFunction(this, FName("OnSeePlayer"));
	EnemySense->OnSeePawn.Add(OnSeePlayerDelegate);

	ResourceIndex = 3;
}

void AKlEnemyCharacter::CreateFlobObject()
{
	TSharedPtr<ResourceAttribute> ResourceAttr = *FKlDataHandle::Get()->ResourceAttrMap.Find(ResourceIndex);

	for (TArray<TArray<int>>::TIterator It(ResourceAttr->FlobObjectInfo); It; ++It)
	{
		FRandomStream Stream;
		Stream.GenerateNewSeed();
		int Num = Stream.RandRange((*It)[1], (*It)[2]);

		if (GetWorld())
		{
			for (int i = 0; i < Num; ++i)
			{
				// Spawn flob objects
				AKlFlobObject* FlobObject = GetWorld()->SpawnActor<AKlFlobObject>(
					GetActorLocation() + FVector(0.f, 0.f, 40.f), 
					FRotator::ZeroRotator
				);

				FlobObject->CreateFlobObject((*It)[0]);
			}
		}
	}
}

void AKlEnemyCharacter::OnSeePlayer(APawn* PlayerChar)
{
	if (Cast<AKlPlayerCharacter>(PlayerChar)) {
		// Notify the controller OnSeePlayer event
		if (EnemyController) EnemyController->OnSeePlayer();
		FKlHelper::Debug(FString("Enemy see player."), 3.f);
	}
}

// Called every frame
void AKlEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AKlEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AKlEnemyCharacter::UpdateHPBarRotation(FVector PlayerLocation)
{
	FVector StartPos(GetActorLocation().X, GetActorLocation().Y, 0);
	FVector TargetPos(PlayerLocation.X, PlayerLocation.Y, 0.f);

	HPBar->SetWorldRotation(FRotationMatrix::MakeFromX(TargetPos - StartPos).Rotator());
}

void AKlEnemyCharacter::SetMaxSpeed(float Speed)
{
	GetCharacterMovement()->MaxWalkSpeed = Speed;
}

float AKlEnemyCharacter::GetIdleWaitTime()
{
	// If Animation Inst isn't exists, return 3 s
	if (!EnemyAnimInst) return 3.f;
	
	// Generate random seed
	FRandomStream Stream;
	Stream.GenerateNewSeed();
	int IdleTpye = Stream.RandRange(0, 2);
	float AnimLength = EnemyAnimInst->SetIdleType(IdleTpye);
	Stream.GenerateNewSeed();
	int AnimCount = Stream.RandRange(1, 3);

	return AnimLength * AnimCount;
}

float AKlEnemyCharacter::PlayAttackAction(EEnemyAttackType AttackType)
{
	if (!EnemyAnimInst) 
		return 0.f;

	return EnemyAnimInst->PlayAttackAction(AttackType);
}

float AKlEnemyCharacter::PlayHurtAction()
{
	if (!EnemyAnimInst) return 0.f;

	return EnemyAnimInst->PlayHurtAction();
}

void AKlEnemyCharacter::StartDefence()
{
	if (EnemyAnimInst)
		EnemyAnimInst->IsDefence = true;
}

void AKlEnemyCharacter::StopDefence()
{
	if (EnemyAnimInst)
		EnemyAnimInst->IsDefence = false;
}

void AKlEnemyCharacter::AcceptDamage(int DamageVal)
{
	// If enemy is in defense state, return immediately
	if (EnemyAnimInst && EnemyAnimInst->IsDefence) 
		return;

	HP = FMath::Clamp<float>(HP - DamageVal, 0.f, 500.f);
	HPBarWidget->ChangeHP(HP / 200.f);

	if (HP == 0.f && !DeadHandle.IsValid())
	{
		EnemyController->EnemyDead();

		EnemyAnimInst->StopAllAction();

		float DeadDuration = 0.f;
		FRandomStream Stream;
		Stream.GenerateNewSeed();
		int SelectIndex = Stream.RandRange(0, 1);
		if (SelectIndex == 0)
		{
			GetMesh()->PlayAnimation(AnimDead_I, false);
			DeadDuration = AnimDead_I->GetMaxCurrentTime() * 2;
		}
		else
		{
			GetMesh()->PlayAnimation(AnimDead_II, false);
			DeadDuration = AnimDead_II->GetMaxCurrentTime() * 2;
		}

		CreateFlobObject();

		FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(this, &AKlEnemyCharacter::DestroyEvent);
		GetWorld()->GetTimerManager().SetTimer(DeadHandle, TimerDelegate, DeadDuration, false);
	}
	else
	{
		if (EnemyController) EnemyController->UpdateDamageRatio(HP / 200.f);
	}
}

void AKlEnemyCharacter::DestroyEvent()
{
	if (DeadHandle.IsValid()) GetWorld()->GetTimerManager().ClearTimer(DeadHandle);

	GetWorld()->DestroyActor(this);
}

FText AKlEnemyCharacter::GetInfoText() const
{
	TSharedPtr<ResourceAttribute> ResourceAttr = *FKlDataHandle::Get()->ResourceAttrMap.Find(ResourceIndex);
	switch (FKlDataHandle::Get()->CurrentCulture)
	{
	case ECultureTeam::EN:
		return ResourceAttr->EN;

		break;
	case ECultureTeam::ZH:
		return ResourceAttr->ZH;

		break;
	}

	return ResourceAttr->ZH;
}

void AKlEnemyCharacter::ChangeWeaponDetect(bool IsOpen)
{
	AKlEnemyTool* WeaponClass = Cast<AKlEnemyTool>(WeaponSocket->GetChildActor());

	if (WeaponClass) 
		WeaponClass->ChangeOverlapDetect(IsOpen);
}

bool AKlEnemyCharacter::IsLockPlayer()
{
	if (EnemyController) 
		return EnemyController->IsLockPlayer;

	return false;
}

void AKlEnemyCharacter::LoadHP(float HPVal)
{
	HP = HPVal;

	HPBarWidget->ChangeHP(HP / 200.f);
}

float AKlEnemyCharacter::GetHP()
{
	return HP;
}

