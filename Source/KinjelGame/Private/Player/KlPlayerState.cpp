// Fill out your copyright notice in the Description page of Project Settings.

#include "KlPlayerState.h"
#include "Data/FKlDataHandle.h"

AKlPlayerState::AKlPlayerState()
{
	CurrentShotcutIndex = 0;
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
