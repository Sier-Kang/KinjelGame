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

	/**
	* Get current object's type
	*/
	EObjectType::Type GetCurrentObjectType() const;

	/**
	* RayInfoWdidget RegisterRayInfo Event
	*/
	void RegisterRayInfoEvent(TSharedPtr<STextBlock> RayInfoTextBlock);

public:
	/** Current shotcut object index */
	int CurrentShotcutIndex;

	// Ray cast Text,PlayerController update.
	FText RayInfoText;

private:
	/**
	* Get Shotcut Information Text
	*/
	FText GetShotcutInfoText() const;

	/**
	* Get Ray info Text
	*/
	FText GetRayInfoText() const;

private:
	/** Shortcut information text */
	TAttribute<FText> ShotcutInfoAttr;

	/** Shotcut container list. */
	TArray<TSharedPtr<ShotcutContainer>> ShortcutContainerList;

	/** Ray cast info atrribute */
	TAttribute<FText> RayInfoTextAttr;
};
