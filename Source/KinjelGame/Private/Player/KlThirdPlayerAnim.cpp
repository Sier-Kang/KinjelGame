// Fill out your copyright notice in the Description page of Project Settings.

#include "KlThirdPlayerAnim.h"
#include "Player/KlPlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

UKlThirdPlayerAnim::UKlThirdPlayerAnim()
{
	bInAir = false;

	Direction = 0.f;
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
