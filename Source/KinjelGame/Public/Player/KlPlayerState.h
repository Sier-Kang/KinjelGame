// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Data/FKlTypes.h"

#include "KlPlayerState.generated.h"

class STextBlock;

/**
 * 
 */
UCLASS()
class KINJELGAME_API AKlPlayerState : public APlayerState
{
	GENERATED_BODY()
public:
	AKlPlayerState();

public:
	/**
	* Register shotcut object container
	*/
	void RegisterShotcunContainer(TArray<TSharedPtr<struct ShotcutContainer>>* ContainerList,
		TSharedPtr<STextBlock> ShotcutInfoTextBlock);

	/**
	* Switch shotcut index when mouse wheel rolls
	*/
	void ChangeShotcut(bool IsPre);

	/**
	* Get Current HandObject Index
	*/
	int GetCurrentHandObjectIndex() const;

public:
	/** Current shotcut object index */
	int CurrentShotcutIndex;

private:
	/**
	* Get Shotcut Information Text
	*/
	FText GetShotcutInfoText() const;

private:
	/** Shortcut information text */
	TAttribute<FText> ShotcutInfoText;

	/** Shotcut container list. */
	TArray<TSharedPtr<ShotcutContainer>> ShortcutContainerList;
};
