// Fill out your copyright notice in the Description page of Project Settings.

#include "KlThirdPlayerAnim.h"
#include "Player/KlPlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ConstructorHelpers.h"
#include "Animation/AnimMontage.h"
#include "Data/FKlTypes.h"

UKlThirdPlayerAnim::UKlThirdPlayerAnim()
{
	bInAir = false;

	Direction = 0.f;

	AnimView = EGameViewMode::Third;

	// Bind Montage resources
	static ConstructorHelpers::FObjectFinder<UAnimMontage> PlayerHitMon(
		TEXT("AnimSequence'/Game/Res/PolygonAdventure/Mannequin/Player/Animation/UpperBody/Player_Hit.Player_Hit'")
	);
	PlayerHitMontage = PlayerHitMon.Object;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> PlayerEatMon(
		TEXT("AnimMontage'/Game/Res/PolygonAdventure/Mannequin/Player/Animation/UpperBody/PlayerEatMontage.PlayerEatMontage'")
	);
	PlayerEatMontage = PlayerEatMon.Object;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> PlayerFightMon(
		TEXT("AnimMontage'/Game/Res/PolygonAdventure/Mannequin/Player/Animation/UpperBody/PlayerFightMontage.PlayerFightMontage'")
	);
	PlayerFightMontage = PlayerFightMon.Object;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> PlayerPunchMon(
		TEXT("AnimMontage'/Game/Res/PolygonAdventure/Mannequin/Player/Animation/UpperBody/PlayerPunchMontage.PlayerPunchMontage'")
	);
	PlayerPunchMontage = PlayerPunchMon.Object;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> PlayerPickUpMon(
		TEXT("AnimMontage'/Game/Res/PolygonAdventure/Mannequin/Player/Animation/UpperBody/PlayerPickUpMontage.PlayerPickUpMontage'")
	);
	PlayerPickUpMontage = PlayerPickUpMon.Object;
}

void UKlThirdPlayerAnim::UpdateParameters()
{
	Super::UpdateParameters();

	if (!PlayerCharacter) return;

	bInAir = PlayerCharacter->GetCharacterMovement()->IsFalling();

	// Calculate angle between camera and movement
	float DeltaAngle= PlayerCharacter->GetVelocity().ToOrientationRotator().Yaw - PlayerCharacter->GetActorRotation().Yaw;

	// Arranged Angle.
	if (DeltaAngle > 180.f)
	{
		DeltaAngle -= 360.f;
	}
	if (DeltaAngle < -180.f)
	{
		DeltaAngle += 360.f;
	}

	Direction = DeltaAngle;
}
