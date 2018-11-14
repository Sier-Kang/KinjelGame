// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/FKlTypes.h"
#include "UI/Widgets/Package/SKlContainerBaseWidget.h"

/**
 * 
 */
class KINJELGAME_API KlPackageManager
{
public:
	KlPackageManager();
	
	static void Initialize();

	/** Get Singleton inst of Package Manager */
	static TSharedPtr<KlPackageManager> Get();

	/** Add container */
	void InsertContainer(TSharedPtr<class SKlContainerBaseWidget> Container, EContainerType::Type InsertType);

	/** Update container's color when cursor hover */
	void UpdateHovered(FVector2D MousePos, FGeometry PackGeo);

	/** Left mouse button event */
	void LeftOption(FVector2D MousePos, FGeometry PackGeo);

	/** Right mouse button event */
	void RightOption(FVector2D MousePos, FGeometry PackGeo);

	/** Query for object space */
	bool SearchFreeSpace(int ObjectID);

	/** Add object */
	void AddObject(int ObjectID);

	/** Eat object 
	* @param Shortcut ID
	* @return Eat success or not
	*/
	bool EatUpEvent(int ShortcutID);

	/** Load record */
	void LoadRecord(TArray<int32>* InputIndex, TArray<int32>* InputNum, TArray<int32>* NormalIndex, 
		TArray<int32>* NormalNum, TArray<int32>* ShortcutIndex, TArray<int32>* ShortcutNum);

	void SaveData(TArray<int32>& InputIndex, TArray<int32>& InputNum, TArray<int32>& NormalIndex, 
		TArray<int32>& NormalNum, TArray<int32>& ShortcutIndex, TArray<int32>& ShortcutNum);

public:
	/** Mouse cursor object ID */
	int ObjectIndex;

	/** Mouse cursor object Quantity */
	int ObjectNum;

	/** Delegate to bind with PlayerState's PlayerThrowObject method */
	FThrowObject PlayerThrowObject;
	/** Change shortcut info */
	FPackShortChange ChangeHandObject;

private:
	static TSharedPtr<KlPackageManager> Create();

	/** Get container that cursor hovered */
	TSharedPtr<SKlContainerBaseWidget> LocateContainer(FVector2D MousePos, FGeometry PackGeo);

	/** Throw Object event */
	void ThrowObject(int ObjectID, int Num);

	/** Compound Output Event */
	void CompoundOutput(int ObjectID, int Num);

	/** Compound Input Event */
	void CompoundInput();

	/** Change event of shortcut */
	void PackShortChange(int ShortcutID, int ObjectID, int ObjectNum);

	/** Get Flag If can add */
	bool MultiplyAble(int ObjectID);

	/**
	* Weather has space to insert object
	* @param Object ID
	* @param [Out] Container ptr that can insert object
	* @return weather can insert
	*/
	bool SearchFreeSpace(int ObjectID, TSharedPtr<SKlContainerBaseWidget>& FreeContainer);

private:
	// Singleton Inst
	static TSharedPtr<KlPackageManager> PackageInstance;

	/** Container List */
	TArray<TSharedPtr<SKlContainerBaseWidget>> InputContainerList;
	TArray<TSharedPtr<SKlContainerBaseWidget>> NormalContainerList;
	TArray<TSharedPtr<SKlContainerBaseWidget>> ShortcutContainerList;

	/** Output container */
	TSharedPtr<SKlContainerBaseWidget > OutputContainer;

	/** Pre container that mouse cursor hovered */
	TSharedPtr<SKlContainerBaseWidget> LastHoveredCon;
};

