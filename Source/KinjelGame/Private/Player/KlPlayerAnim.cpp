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
}
