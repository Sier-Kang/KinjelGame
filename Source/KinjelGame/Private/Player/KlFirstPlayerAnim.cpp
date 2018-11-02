// Fill out your copyright notice in the Description page of Project Settings.

#include "KlFirstPlayerAnim.h"
#include "ConstructorHelpers.h"
#include "Animation/AnimMontage.h"
#include "Data/FKlTypes.h"

UKlFirstPlayerAnim::UKlFirstPlayerAnim()
{
	AnimView = EGameViewMode::First;

	// Bind Montage resources.
	static ConstructorHelpers::FObjectFinder<UAnimMontage> PlayerHitMon(
		TEXT("AnimMontage'/Game/Res/PolygonAdventure/Mannequin/FirstPlayer/Animation/UpperBody/FirstPlayerHitMontage.FirstPlayerHitMontage'")
	);
	PlayerHitMontage = PlayerHitMon.Object;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> PlayerEatMon(
		TEXT("AnimMontage'/Game/Res/PolygonAdventure/Mannequin/FirstPlayer/Animation/UpperBody/FirstPlayerEatMontage.FirstPlayerEatMontage'")
	);
	PlayerEatMontage = PlayerEatMon.Object;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> PlayerFightMon(
		TEXT("AnimMontage'/Game/Res/PolygonAdventure/Mannequin/FirstPlayer/Animation/UpperBody/FirstPlayerFightMontage.FirstPlayerFightMontage'")
	);
	PlayerFightMontage = PlayerFightMon.Object;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> PlayerPunchMon(
		TEXT("AnimMontage'/Game/Res/PolygonAdventure/Mannequin/FirstPlayer/Animation/UpperBody/FirstPlayerPunchMontage.FirstPlayerPunchMontage'")
	);
	PlayerPunchMontage = PlayerPunchMon.Object;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> PlayerPickUpMon(
		TEXT("AnimMontage'/Game/Res/PolygonAdventure/Mannequin/FirstPlayer/Animation/UpperBody/FirstPlayerPickUpMontage.FirstPlayerPickUpMontage'")
	);
	PlayerPickUpMontage = PlayerPickUpMon.Object;
}
