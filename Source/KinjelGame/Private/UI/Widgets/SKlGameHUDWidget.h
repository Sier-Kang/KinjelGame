// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SlateBasics.h"
#include "Widgets/SCompoundWidget.h"
#include "Data/FKlTypes.h"

/**
 * 
 */
class SKlGameHUDWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SKlGameHUDWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;

	/** Bind to UIScaler */
	float GetUIScaler() const;

	/**
	* Display Game UI
	* @param PreUI current UI
	* @param NextUI UI comes to display
	*/
	void ShowGameUI(EGameUIType::Type PreUI, EGameUIType::Type NextUI);

public:
	/** Shortcut Panel in game menu - Center/Bottom */
	TSharedPtr<class SKlShotcutWidget> ShotcutWidget;

	/** Ray cast object's name in game menu - Center/Top */
	TSharedPtr<class SKlRayInfoWidget> RayInfoWidget;

	/** Pointer insight in game - Center/Center */
	TSharedPtr<class SKlPointerWidget> PointerWidget;

	/** Player State widget */
	TSharedPtr<class SKlPlayerStateWidget> PlayerStateWidget;

	/** Game menu in game */
	TSharedPtr<class SKlGameMenuWidget> GameMenuWidget;

	/** ChatRoom Widget */
	TSharedPtr<class SKlChatRoomWidget> ChatRoomWidget;

	/** Package Widget */
	TSharedPtr<class SKlPackageWidget> PackageWidget;

	/** Mini Map Widget */
	TSharedPtr<class SKlMiniMapWidget> MiniMapWidget;

	TSharedPtr<class SKlChatShowWidget> ChatShowWidget;
private:
	/**
	* Get screen size
	*/
	FVector2D GetViewportSize() const;

	/**
	* Initialize Game UI map
	*/
	void InitUIMap();

private:
	// DPI Setting
	TAttribute<float> UIScaler;

	// Black Mask
	TSharedPtr<class SBorder> BlackShade;

	/** UI Map */
	TMap<EGameUIType::Type, TSharedPtr<SCompoundWidget>> UIMap;

	/** Message timer */
	float MessageTimeCount;
};
