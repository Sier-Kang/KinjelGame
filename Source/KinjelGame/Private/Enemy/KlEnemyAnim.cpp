// Fill out your copyright notice in the Description page of Project Settings.

#include "KlEnemyAnim.h"
#include "ConstructorHelpers.h"
#include "Enemy/KlEnemyCharacter.h"

UKlEnemyAnim::UKlEnemyAnim()
{
	// Get Animations of Sequence and Montage
	static ConstructorHelpers::FObjectFinder<UAnimSequence> StaticAnimIdle_I(
		TEXT("AnimSequence'/Game/Res/PolygonAdventure/Mannequin/Enemy/Animation/MoveGroup/Enemy_Idle_I.Enemy_Idle_I'")
	);
	AnimIdle_I = StaticAnimIdle_I.Object;

	static ConstructorHelpers::FObjectFinder<UAnimSequence> StaticAnimIdle_II(
		TEXT("AnimSequence'/Game/Res/PolygonAdventure/Mannequin/Enemy/Animation/MoveGroup/Enemy_Idle_II.Enemy_Idle_II'")
	);
	AnimIdle_II = StaticAnimIdle_II.Object;

	static ConstructorHelpers::FObjectFinder<UAnimSequence> StaticAnimIdle_III(
		TEXT("AnimSequence'/Game/Res/PolygonAdventure/Mannequin/Enemy/Animation/MoveGroup/Enemy_Idle_III.Enemy_Idle_III'")
	);
	AnimIdle_III = StaticAnimIdle_III.Object;


	static ConstructorHelpers::FObjectFinder<UAnimMontage> StaticAnimAttack_I(
		TEXT("AnimMontage'/Game/Res/PolygonAdventure/Mannequin/Enemy/Animation/FightGroup/MonEnemy_Attack_I.MonEnemy_Attack_I'")
	);
	AnimAttack_I = StaticAnimAttack_I.Object;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> StaticAnimAttack_II(
		TEXT("AnimMontage'/Game/Res/PolygonAdventure/Mannequin/Enemy/Animation/FightGroup/MonEnemy_Attack_II.MonEnemy_Attack_II'")
	);
	AnimAttack_II = StaticAnimAttack_II.Object;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> StaticAnimAttack_III(
		TEXT("AnimMontage'/Game/Res/PolygonAdventure/Mannequin/Enemy/Animation/FightGroup/MonEnemy_Attack_III.MonEnemy_Attack_III'")
	);
	AnimAttack_III = StaticAnimAttack_III.Object;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> StaticAnimAttack_IV(
		TEXT("AnimMontage'/Game/Res/PolygonAdventure/Mannequin/Enemy/Animation/FightGroup/MonEnemy_Attack_IV.MonEnemy_Attack_IV'")
	);
	AnimAttack_IV = StaticAnimAttack_IV.Object;


	static ConstructorHelpers::FObjectFinder<UAnimSequence> StaticAnimAttackSeq_III(
		TEXT("AnimSequence'/Game/Res/PolygonAdventure/Mannequin/Enemy/Animation/FightGroup/Enemy_Attack_III.Enemy_Attack_III'")
	);
	AnimAttackSeq_III = StaticAnimAttackSeq_III.Object;

	static ConstructorHelpers::FObjectFinder<UAnimSequence> StaticAnimAttackSeq_IV(
		TEXT("AnimSequence'/Game/Res/PolygonAdventure/Mannequin/Enemy/Animation/FightGroup/Enemy_Attack_IV.Enemy_Attack_IV'")
	);
	AnimAttackSeq_IV = StaticAnimAttackSeq_IV.Object;


	static ConstructorHelpers::FObjectFinder<UAnimMontage> StaticAnimHurt(
		TEXT("AnimMontage'/Game/Res/PolygonAdventure/Mannequin/Enemy/Animation/FightGroup/MonEnemy_Hurt.MonEnemy_Hurt'")
	);
	AnimHurt = StaticAnimHurt.Object;

	// Initialize parameters
	Speed = 0.f;

	IdleType = 0.f;

	RootBonePos = FVector::ZeroVector;
	RootBoneAlpha = 0.f;

	CurrentPlayTime = 0.f;

	StartYPos = 0.f;

	IsDefence = false;
}

void UKlEnemyAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	// Initialize EnemyCharacter
	if (!EnemyCharacter) EnemyCharacter = Cast<AKlEnemyCharacter>(TryGetPawnOwner());
	if (!EnemyCharacter) return;

	// Set Speed
	Speed = EnemyCharacter->GetVelocity().Size();

	// If playing Attack_III, modify root bone in real time
	if (Montage_IsPlaying(AnimAttack_III))
	{
		CurrentPlayTime += DeltaSeconds;
		CurrentPlayTime = FMath::Clamp<float>(CurrentPlayTime, 0.f, AnimAttackSeq_III->GetPlayLength());
		FTransform OutputTrans;
		AnimAttackSeq_III->GetBoneTransform(OutputTrans, 0.f, CurrentPlayTime, true);
		RootBonePos = FVector(OutputTrans.GetLocation().X, StartYPos, OutputTrans.GetLocation().Z);
	}

	//If playing Attack_IV, modify root bone in real time
	if (Montage_IsPlaying(AnimAttack_IV))
	{
		CurrentPlayTime += DeltaSeconds;
		CurrentPlayTime = FMath::Clamp<float>(CurrentPlayTime, 0.f, AnimAttackSeq_IV->GetPlayLength());
		FTransform OutputTrans;
		AnimAttackSeq_IV->GetBoneTransform(OutputTrans, 0.f, CurrentPlayTime, true);
		RootBonePos = FVector(OutputTrans.GetLocation().X, StartYPos, OutputTrans.GetLocation().Z);
	}

	// If already do not play attack action, but RootBoneAlpha is still > 0, reset it in 0.3s.
	if (!Montage_IsPlaying(AnimAttack_III) && !Montage_IsPlaying(AnimAttack_IV) && RootBoneAlpha > 0.f)
	{
		RootBoneAlpha -= DeltaSeconds * 3;
		if (RootBoneAlpha < 0.f) RootBoneAlpha = 0.f;
	}
}

float UKlEnemyAnim::SetIdleType(int NewType)
{
	IdleType = FMath::Clamp<float>((float)NewType, 0.f, 2.f);

	switch (NewType)
	{
	case 0:
		return AnimIdle_I->GetPlayLength();

	case 1:
		return AnimIdle_II->GetPlayLength();

	case 2:
		return AnimIdle_III->GetPlayLength();
	}

	return AnimIdle_I->GetPlayLength();
}

float UKlEnemyAnim::PlayAttackAction(EEnemyAttackType AttackType)
{
	FRandomStream Stream;
	Stream.GenerateNewSeed();
	int SelectIndex = Stream.RandRange(0, 1);
	FTransform OutputTrans;

	switch (AttackType)
	{
	case EEnemyAttackType::EA_Normal:
		// Choose normal attack action in random
		if (SelectIndex == 0)
		{
			Montage_Play(AnimAttack_I);

			return AnimAttack_I->GetPlayLength();
		}
		else
		{
			Montage_Play(AnimAttack_II);

			return AnimAttack_II->GetPlayLength();
		}

		break;
	case EEnemyAttackType::EA_Dash:
		{
			// Play Attack_III
			Montage_Play(AnimAttack_III);
			CurrentPlayTime = 0.f;
			RootBonePos = FVector::ZeroVector;
			RootBoneAlpha = 1.f;
			// Get first frame Y Position
			AnimAttackSeq_III->GetBoneTransform(OutputTrans, 0, 0.f, true);
			StartYPos = OutputTrans.GetLocation().Y;
		
			return AnimAttack_III->GetPlayLength();
		}

		break;
	case EEnemyAttackType::EA_Pursuit:
		{
			Montage_Play(AnimAttack_IV);
			CurrentPlayTime = 0;
			RootBonePos = FVector::ZeroVector;
			RootBoneAlpha = 1.f;
			//Get first frame Y Position
			AnimAttackSeq_IV->GetBoneTransform(OutputTrans, 0, 0.f, true);
			StartYPos = OutputTrans.GetLocation().Y;

			return AnimAttack_IV->GetPlayLength();
		}

		break;
	}

	return 0.f;
}

float UKlEnemyAnim::PlayHurtAction()
{
	if (!Montage_IsPlaying(AnimHurt)) Montage_Play(AnimHurt);

	return AnimHurt->GetPlayLength();
}

void UKlEnemyAnim::StopAllAction()
{
	Montage_Stop(0);
}

void UKlEnemyAnim::ChangeDetection(bool IsOpen)
{
	//if (EnemyCharacter) EnemyCharacter->ChangeWeaponDetect(IsOpen);
}
