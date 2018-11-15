// Fill out your copyright notice in the Description page of Project Settings.

#include "KlPackageManager.h"
#include "Data/FKlDataHandle.h"


TSharedPtr<KlPackageManager> KlPackageManager::PackageInstance = nullptr;

KlPackageManager::KlPackageManager()
{
	ObjectIndex = 0;

	ObjectNum = 0;
}

void KlPackageManager::Initialize()
{
	if (!PackageInstance.IsValid())
		PackageInstance = Create();
}

TSharedPtr<KlPackageManager> KlPackageManager::Get()
{
	Initialize();

	return PackageInstance;
}

void KlPackageManager::InsertContainer(TSharedPtr<class SKlContainerBaseWidget> Container, EContainerType::Type InsertType)
{
	switch (InsertType)
	{
	case EContainerType::Output:
		OutputContainer = Container;
		OutputContainer->CompoundOutput.BindRaw(this, &KlPackageManager::CompoundOutput);
		OutputContainer->ThrowObject.BindRaw(this, &KlPackageManager::ThrowObject);

		break;
	case EContainerType::Input:
		Container->CompoundInput.BindRaw(this, &KlPackageManager::CompoundInput);
		InputContainerList.Add(Container);

		break;
	case EContainerType::Normal:
		NormalContainerList.Add(Container);

		break;
	case EContainerType::Shortcut:
		Container->PackShortChange.BindRaw(this, &KlPackageManager::PackShortChange);
		ShortcutContainerList.Add(Container);

		break;
	}
}

void KlPackageManager::UpdateHovered(FVector2D MousePos, FGeometry PackGeo)
{
	// Get hovered container 
	TSharedPtr<SKlContainerBaseWidget> CurrHoveredCon = LocateContainer(MousePos, PackGeo);

	if (CurrHoveredCon.IsValid())
	{
		CurrHoveredCon->UpdateHovered(true);

		if (LastHoveredCon.IsValid() && LastHoveredCon.Get() != CurrHoveredCon.Get()) {
			LastHoveredCon->UpdateHovered(false);
		}
	}
	else
	{
		if (LastHoveredCon.IsValid()) {
			LastHoveredCon->UpdateHovered(false);
		}
	}

	LastHoveredCon = CurrHoveredCon;
}

void KlPackageManager::LeftOption(FVector2D MousePos, FGeometry PackGeo)
{
	TSharedPtr<SKlContainerBaseWidget> ClickedContainer = LocateContainer(MousePos, PackGeo);
	//If exists, run its event
	if (ClickedContainer.IsValid())
	{
		ClickedContainer->LeftOperate(ObjectIndex, ObjectNum, ObjectIndex, ObjectNum);
	}

	if (!ClickedContainer.IsValid() && ObjectIndex != 0)
	{
		ThrowObject(ObjectIndex, ObjectNum);

		ObjectIndex = ObjectNum = 0;
	}
}

void KlPackageManager::RightOption(FVector2D MousePos, FGeometry PackGeo)
{
	TSharedPtr<SKlContainerBaseWidget> ClickedContainer = LocateContainer(MousePos, PackGeo);

	if (ClickedContainer.IsValid()) {
		ClickedContainer->RightOperate(ObjectIndex, ObjectNum, ObjectIndex, ObjectNum);
	}
}

TSharedPtr<KlPackageManager> KlPackageManager::Create()
{
	TSharedRef<KlPackageManager> PackageRef = MakeShareable(new KlPackageManager());

	return PackageRef;
}

TSharedPtr<SKlContainerBaseWidget> KlPackageManager::LocateContainer(FVector2D MousePos, FGeometry PackGeo)
{
	for (TArray<TSharedPtr<SKlContainerBaseWidget>>::TIterator It(ShortcutContainerList); It; ++It) {
		// Get region
		FVector2D StartPos = PackGeo.AbsoluteToLocal((*It)->GetCachedGeometry().AbsolutePosition);
		FVector2D EndPos = StartPos + FVector2D(80.f, 80.f);

		// Mouse in this region, if true, return its container
		if (MousePos.X >= StartPos.X && MousePos.X <= EndPos.X && MousePos.Y >= StartPos.Y && MousePos.Y <= EndPos.Y)
		{
			return *It;
		}
	}

	for (TArray<TSharedPtr<SKlContainerBaseWidget>>::TIterator It(NormalContainerList); It; ++It) {
		FVector2D StartPos = PackGeo.AbsoluteToLocal((*It)->GetCachedGeometry().AbsolutePosition);
		FVector2D EndPos = StartPos + FVector2D(80.f, 80.f);

		if (MousePos.X >= StartPos.X && MousePos.X <= EndPos.X && MousePos.Y >= StartPos.Y && MousePos.Y <= EndPos.Y) {
			return *It;
		}
	}

	for (TArray<TSharedPtr<SKlContainerBaseWidget>>::TIterator It(InputContainerList); It; ++It) {
		FVector2D StartPos = PackGeo.AbsoluteToLocal((*It)->GetCachedGeometry().AbsolutePosition);
		FVector2D EndPos = StartPos + FVector2D(80.f, 80.f);
		if (MousePos.X >= StartPos.X && MousePos.X <= EndPos.X && MousePos.Y >= StartPos.Y && MousePos.Y <= EndPos.Y) {
			return *It;
		}
	}
	// Output container
	FVector2D StartPos = PackGeo.AbsoluteToLocal(OutputContainer->GetCachedGeometry().AbsolutePosition);
	FVector2D EndPos = StartPos + FVector2D(80.f, 80.f);

	if (MousePos.X >= StartPos.X && MousePos.X <= EndPos.X && MousePos.Y >= StartPos.Y && MousePos.Y <= EndPos.Y) {
		return OutputContainer;
	}

	return nullptr;
}

void KlPackageManager::ThrowObject(int ObjectID, int Num)
{
	PlayerThrowObject.ExecuteIfBound(ObjectID, Num);
}

void KlPackageManager::CompoundOutput(int ObjectID, int Num)
{
	if (ObjectID == 0) return;

	TArray<int> TableMap;
	for (TArray<TSharedPtr<SKlContainerBaseWidget>>::TIterator It(InputContainerList); It; ++It) {
		TableMap.Add((*It)->GetIndex());
	}
	TableMap.Add(ObjectID);

	TArray<int> ExpendMap;
	for (TArray<TSharedPtr<CompoundTable>>::TIterator It(FKlDataHandle::Get()->CompoundTableMap); It; ++It) {
		if ((*It)->DetectExpend(&TableMap, Num, ExpendMap)) break;
	}

	if (ExpendMap.Num() != 9) return;

	for (int i = 0; i < 9; ++i) {
		int InputID = (InputContainerList[i]->GetNum() - ExpendMap[i] <= 0) ? 0 : InputContainerList[i]->GetIndex();
		int InputNum = (InputID == 0) ? 0 : (InputContainerList[i]->GetNum() - ExpendMap[i]);

		InputContainerList[i]->ResetContainerPara(InputID, InputNum);
	}
}

void KlPackageManager::CompoundInput()
{
	TArray<int> IDMap;
	TArray<int> NumMap;
	for (TArray<TSharedPtr<SKlContainerBaseWidget>>::TIterator It(InputContainerList); It; ++It) {
		IDMap.Add((*It)->GetIndex());
		NumMap.Add((*It)->GetNum());
	}

	int OutputIndex = 0;
	int OutputNum = 0;

	for (TArray<TSharedPtr<CompoundTable>>::TIterator It(FKlDataHandle::Get()->CompoundTableMap); It; ++It) {
		(*It)->DetectTable(&IDMap, &NumMap, OutputIndex, OutputNum);
		if (OutputIndex != 0 && OutputNum != 0) break;
	}

	if (MultiplyAble(OutputIndex)) {
		OutputContainer->ResetContainerPara(OutputIndex, OutputNum);
	}
	else {
		OutputContainer->ResetContainerPara(OutputIndex, 1);
	}
}

void KlPackageManager::PackShortChange(int ShortcutID, int ObjectID, int ObjectNum)
{
	// Bind delegate of PlayerState's ChangeHandObject,Under player character
	ChangeHandObject.ExecuteIfBound(ShortcutID, ObjectID, ObjectNum);
}

bool KlPackageManager::MultiplyAble(int ObjectID)
{
	// Get Object property
	TSharedPtr<ObjectAttribute> ObjectAttr = *FKlDataHandle::Get()->ObjectAttrMap.Find(ObjectID);

	// Its type is weapon or tool
	return (ObjectAttr->ObjectType != EObjectType::Tool && ObjectAttr->ObjectType != EObjectType::Weapon);
}

bool KlPackageManager::SearchFreeSpace(int ObjectID, TSharedPtr<SKlContainerBaseWidget>& FreeContainer)
{
	TSharedPtr<SKlContainerBaseWidget> EmptyContainer;

	for (TArray<TSharedPtr<SKlContainerBaseWidget>>::TIterator It(ShortcutContainerList); It; ++It) {
		if (!EmptyContainer.IsValid()) {
			if ((*It)->IsEmpty()) EmptyContainer = *It;
		}

		if (!FreeContainer.IsValid())
		{
			if ((*It)->RemainSpace(ObjectID))
			{
				FreeContainer = *It;
				return true;
			}
		}
	}

	for (TArray<TSharedPtr<SKlContainerBaseWidget>>::TIterator It(NormalContainerList); It; ++It) {
		if (!EmptyContainer.IsValid()) {
			if ((*It)->IsEmpty()) EmptyContainer = *It;
		}

		if (!FreeContainer.IsValid())
		{
			if ((*It)->RemainSpace(ObjectID))
			{
				FreeContainer = *It;
				return true;
			}
		}
	}

	if (EmptyContainer.IsValid()) {
		FreeContainer = EmptyContainer;
		return true;
	}

	return false;
}

bool KlPackageManager::SearchFreeSpace(int ObjectID)
{
	TSharedPtr<SKlContainerBaseWidget> FreeContainer;

	return SearchFreeSpace(ObjectID, FreeContainer);
}

void KlPackageManager::AddObject(int ObjectID)
{
	TSharedPtr<SKlContainerBaseWidget> FreeContainer;

	if (SearchFreeSpace(ObjectID, FreeContainer)) {
		FreeContainer->AddObject(ObjectID);
	}
}

bool KlPackageManager::EatUpEvent(int ShortcutID)
{
	TSharedPtr<ObjectAttribute> ObjectAttr = *FKlDataHandle::Get()->ObjectAttrMap.Find(ShortcutContainerList[ShortcutID]->GetIndex());

	if (ObjectAttr->ObjectType == EObjectType::Food)
	{
		int NewNum = (ShortcutContainerList[ShortcutID]->GetNum() - 1) < 0 ? 0 : (ShortcutContainerList[ShortcutID]->GetNum() - 1);

		int NewIndex = NewNum == 0 ? 0 : ShortcutContainerList[ShortcutID]->GetIndex();

		ShortcutContainerList[ShortcutID]->ResetContainerPara(NewIndex, NewNum);

		return true;
	}

	return false;
}

void KlPackageManager::LoadRecord(TArray<int32>* InputIndex, TArray<int32>* InputNum, TArray<int32>* NormalIndex, TArray<int32>* NormalNum, TArray<int32>* ShortcutIndex, TArray<int32>* ShortcutNum)
{
	for (int i = 0; i < InputContainerList.Num(); ++i)
	{
		if ((*InputIndex)[i] != 0) 
			InputContainerList[i]->ResetContainerPara((*InputIndex)[i], (*InputNum)[i]);
	}

	for (int i = 0; i < NormalContainerList.Num(); ++i) {
		if ((*NormalIndex)[i] != 0) 
			NormalContainerList[i]->ResetContainerPara((*NormalIndex)[i], (*NormalNum)[i]);
	}

	for (int i = 0; i < ShortcutContainerList.Num(); ++i) {
		if ((*ShortcutIndex)[i] != 0) 
			ShortcutContainerList[i]->ResetContainerPara((*ShortcutIndex)[i], (*ShortcutNum)[i]);
	}
}

void KlPackageManager::SaveData(TArray<int32>& InputIndex, TArray<int32>& InputNum, TArray<int32>& NormalIndex, TArray<int32>& NormalNum, TArray<int32>& ShortcutIndex, TArray<int32>& ShortcutNum)
{
	for (int i = 0; i < InputContainerList.Num(); ++i)
	{
		InputIndex.Add(InputContainerList[i]->GetIndex());
		InputNum.Add(InputContainerList[i]->GetNum());
	}

	for (int i = 0; i < NormalContainerList.Num(); ++i) {
		NormalIndex.Add(NormalContainerList[i]->GetIndex());
		NormalNum.Add(NormalContainerList[i]->GetNum());
	}

	for (int i = 0; i < ShortcutContainerList.Num(); ++i) {
		ShortcutIndex.Add(ShortcutContainerList[i]->GetIndex());
		ShortcutNum.Add(ShortcutContainerList[i]->GetNum());
	}
}

