// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Data/FKlTypes.h"

#include "KlPlayerState.generated.h"

class STextBlock;

// Update player state widget delegate
DECLARE_DELEGATE_TwoParams(FUpdateStateWidget, float, float)

/**
 * 
 */
UCLASS()
class KINJELGAME_API AKlPlayerState : public APlayerState
{
	GENERATED_BODY()
public:
	AKlPlayerState();

	virtual void Tick(float DeltaSeconds) override;

protected:
	virtual void BeginPlay() override;

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

	/**
	* Get Affect Range of the object in character's hand
	*/
	int GetAffectRange() const;

	/**
	* Get damage value of object in character's hand
	*/
	int GetDamageValue(EResourceType::Type ResourceType) const;

	/**
	* Change shortcut info
	*/
	void ChangeHandObject(int ShortcutID, int ObjectID, int ObjectNum);

	/**
	* Promote character's Hunger Value
	*/
	void PromoteHunger();

	/** Is player dead */
	bool IsPlayerDead();

	/** Accept damage */
	void AcceptDamage(int DamageVal);

	/** Load Hp and hunger */
	void LoadState(float HPVal, float HungerVal);

	/** Save player's HP and Hunger */
	void SaveState(float& HPVal, float HungerVal);

public:
	/** Player Controller */
	class AKlPlayerController* PlayerController;

	/** Current shotcut object index */
	int CurrentShotcutIndex;

	// Ray cast Text,PlayerController update.
	FText RayInfoText;

	/** Player state widget delegate */
	FUpdateStateWidget UpdateStateWidget;
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

	/** HP and Hunger */
	float HP;

	float Hunger;

	/** Player Dead Flag */
	bool IsDead;
};
