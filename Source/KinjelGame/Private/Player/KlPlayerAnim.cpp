// Fill out your copyright notice in the Description page of Project Settings.

#include "KlPlayerAnim.h"
#include "Player/KlPlayerCharacter.h"

UKlPlayerAnim::UKlPlayerAnim()
{
	Speed = 0.f;
	SpineRotator = FRotator(0.f, 0.f, 0.f);
}

void UKlPlayerAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	InitPlayerCharacter();
	UpdateParameters();

	UpdateMontage();
}

void UKlPlayerAnim::ChangeDetection(bool IsOpen)
{
	if (!PlayerCharacter) return;

	PlayerCharacter->ChangeHandObjectDetection(IsOpen);
}

void UKlPlayerAnim::RenderHandObject(bool bIsRender)
{
	if (!PlayerCharacter) return;

	PlayerCharacter->RenderHandObject(bIsRender);
}

void UKlPlayerAnim::EatUpEvent()
{
	if (!PlayerCharacter) return;

	PlayerCharacter->EatUpEvent();
}

void UKlPlayerAnim::InitPlayerCharacter()
{
	if (!PlayerCharacter)
	{
		PlayerCharacter = Cast<AKlPlayerCharacter>(TryGetPawnOwner());
	}
}

void UKlPlayerAnim::UpdateParameters()
{
	if (!PlayerCharacter)
	{ 
		return;
	}

	Speed = PlayerCharacter->GetVelocity().Size();

	// Calculate bone spine's rotation
	float SpineDir = PlayerCharacter->GetActorRotation().Yaw - 90.f;
	if (SpineDir > 180.f) SpineDir -= 360.f;
	if (SpineDir < -180.f) SpineDir += 360.f;

	SpineRotator = FRotator(0.f, SpineDir, 90.f);
}

void UKlPlayerAnim::UpdateMontage()
{
	if (!PlayerCharacter) return;

	// If changing view mode, immediately return
	if (PlayerCharacter->CharacterViewMode != AnimView) return;
	
	// Play montage animation according to its upper body status.
	if (!Montage_GetIsStopped(CurrentMontage)) return; // Do not change upper body's status until played over.

	switch (PlayerCharacter->UpperBodyMode)
	{
	case EUpperBody::None:
	{
		if (CurrentMontage != nullptr) {
			Montage_Stop(0);

			CurrentMontage = nullptr;

			AllowViewChange(true);
		}
	}
	
		break;
	case EUpperBody::Punch:
	{
		if (!Montage_IsPlaying(PlayerPunchMontage))
		{
			Montage_Play(PlayerPunchMontage);

			CurrentMontage = PlayerPunchMontage;

			AllowViewChange(false);
		}
	}

		break;
	case EUpperBody::Hit:
	{
		if (!Montage_IsPlaying(PlayerHitMontage))
		{
			Montage_Play(PlayerHitMontage);

			CurrentMontage = PlayerHitMontage;

			AllowViewChange(false);
		}
	}

		break;
	case EUpperBody::Fight:
	{
		if (!Montage_IsPlaying(PlayerFightMontage))
		{
			Montage_Play(PlayerFightMontage);

			CurrentMontage = PlayerFightMontage;

			AllowViewChange(false);
		}
	}

		break;
	case EUpperBody::PickUp:
	{
		if (!Montage_IsPlaying(PlayerPickUpMontage))
		{
			Montage_Play(PlayerPickUpMontage);

			CurrentMontage = PlayerPickUpMontage;

			AllowViewChange(false);
		}
	}

		break;
	case EUpperBody::Eat:
	{
		if (!Montage_IsPlaying(PlayerEatMontage))
		{
			Montage_Play(PlayerEatMontage);

			CurrentMontage = PlayerEatMontage;

			AllowViewChange(false);
		}
	}

		break;
	default:

		break;
	}
}

void UKlPlayerAnim::AllowViewChange(bool IsAllowed)
{
	if (!PlayerCharacter) return;

	PlayerCharacter->bAllowedSwitchViewMode = IsAllowed;
}
