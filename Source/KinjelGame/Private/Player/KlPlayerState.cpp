// Fill out your copyright notice in the Description page of Project Settings.

#include "KlPlayerState.h"
#include "Data/FKlDataHandle.h"
#include "KlPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

AKlPlayerState::AKlPlayerState()
{
	PrimaryActorTick.bCanEverTick = true;

	CurrentShotcutIndex = 0;

	HP = 500.f;

	Hunger = 600.f;

	IsDead = false;
}

void AKlPlayerState::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// If Hunger reduce to 0, keeping reduce HP
	if (Hunger <= 0) {
		HP -= DeltaSeconds * 2;
	}
	else {
		if (!IsDead) {
			// If Hunger is not 0, reduce 2 per second
			Hunger -= DeltaSeconds * 2;
			// Keep increment HP, 1 per second
			HP += DeltaSeconds;
		}
	}
	// Set range
	HP = FMath::Clamp<float>(HP, 0.f, 500.f);
	Hunger = FMath::Clamp<float>(Hunger, 0.f, 600.f);
	// Run player state delegate
	UpdateStateWidget.ExecuteIfBound(HP / 500.f, Hunger / 500.f);

	if (HP == 0.f && !IsDead) {
		//if (PlayerController)SPController->PlayerDead();

		IsDead = true;
	}
}

void AKlPlayerState::BeginPlay()
{
	Super::BeginPlay();

	// Set Player Controller
	PlayerController = Cast<AKlPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}

void AKlPlayerState::RegisterShotcunContainer(TArray<TSharedPtr<ShotcutContainer>>* ContainerList, TSharedPtr<STextBlock> ShotcutInfoTextBlock)
{
	for (TArray<TSharedPtr<ShotcutContainer>>::TIterator It(*ContainerList); It; It++) {
		ShortcutContainerList.Add(*It);
	}

	ShotcutInfoAttr.BindUObject(this, &AKlPlayerState::GetShotcutInfoText);

	ShotcutInfoTextBlock->SetText(ShotcutInfoAttr);

	// Test data
	ShortcutContainerList[1]->SetObject(2)->SetObjectNum(10);
	ShortcutContainerList[2]->SetObject(1)->SetObjectNum(100);
	ShortcutContainerList[3]->SetObject(4)->SetObjectNum(80);
	ShortcutContainerList[4]->SetObject(3)->SetObjectNum(100);
	ShortcutContainerList[5]->SetObject(7)->SetObjectNum(10);
	ShortcutContainerList[6]->SetObject(5)->SetObjectNum(1);
	ShortcutContainerList[7]->SetObject(6)->SetObjectNum(70);
}

void AKlPlayerState::ChangeShotcut(bool IsPre)
{
	// Next index
	int NextIndex = 0;

	if (IsPre) {
		NextIndex = CurrentShotcutIndex - 1 < 0 ? 8 : CurrentShotcutIndex - 1;
	}
	else {
		NextIndex = CurrentShotcutIndex + 1 > 8 ? 0 : CurrentShotcutIndex + 1;
	}
	ShortcutContainerList[CurrentShotcutIndex]->SetChoosed(false);
	ShortcutContainerList[NextIndex]->SetChoosed(true);

	// Update current Index
	CurrentShotcutIndex = NextIndex;
}

int AKlPlayerState::GetCurrentHandObjectIndex() const
{
	if (ShortcutContainerList.Num() == 0) return 0;

	return ShortcutContainerList[CurrentShotcutIndex]->ObjectIndex;
}

EObjectType::Type AKlPlayerState::GetCurrentObjectType() const
{
	TSharedPtr<ObjectAttribute> ObjectAttr;
	ObjectAttr = *FKlDataHandle::Get()->ObjectAttrMap.Find(GetCurrentHandObjectIndex());

	return ObjectAttr->ObjectType;
}

void AKlPlayerState::RegisterRayInfoEvent(TSharedPtr<STextBlock> RayInfoTextBlock)
{
	RayInfoTextAttr.BindUObject(this, &AKlPlayerState::GetRayInfoText);

	RayInfoTextBlock->SetText(RayInfoTextAttr);
}

int AKlPlayerState::GetAffectRange() const
{
	TSharedPtr<ObjectAttribute> ObjectAttr;
	ObjectAttr = *FKlDataHandle::Get()->ObjectAttrMap.Find(GetCurrentHandObjectIndex());

	return ObjectAttr->AffectRange;
}

int AKlPlayerState::GetDamageValue(EResourceType::Type ResourceType) const
{
	TSharedPtr<ObjectAttribute> ObjectAttr;
	ObjectAttr = *FKlDataHandle::Get()->ObjectAttrMap.Find(GetCurrentHandObjectIndex());

	switch (ResourceType)
	{
	case EResourceType::Plant:
		return ObjectAttr->PlantAttack;

		break;
	case EResourceType::Metal:
		return ObjectAttr->MetalAttack;

		break;
	case EResourceType::Animal:
		return ObjectAttr->AnimalAttack;

		break;
	}

	return ObjectAttr->PlantAttack;
}

FText AKlPlayerState::GetShotcutInfoText() const
{
	TSharedPtr<ObjectAttribute> ObjectAttr;
	ObjectAttr = *FKlDataHandle::Get()->ObjectAttrMap.Find(GetCurrentHandObjectIndex());
	switch (FKlDataHandle::Get()->CurrentCulture)
	{
	case ECultureTeam::EN:
		return ObjectAttr->EN;

		break;
	case ECultureTeam::ZH:
		return ObjectAttr->ZH;

		break;
	}

	return ObjectAttr->ZH;
}

FText AKlPlayerState::GetRayInfoText() const
{
	// Ray Cast info test
	return RayInfoText;
}
