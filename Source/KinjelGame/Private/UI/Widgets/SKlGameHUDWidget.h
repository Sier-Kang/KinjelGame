// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SlateBasics.h"
#include "Widgets/SCompoundWidget.h"

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

	/** Bind to UIScaler */
	float GetUIScaler() const;

public:
	/** Shortcut Panel in game menu - Center/Bottom */
	TSharedPtr<class SKlShotcutWidget> ShotcutWidget;

	/** Ray cast object's name in game menu - Center/Top */
	TSharedPtr<class SKlRayInfoWidget> RayInfoWidget;

	/** Pointer insight in game - Center/Center */
	TSharedPtr<class SKlPointerWidget> PointerWidget;

	/** Player State widget */
	TSharedPtr<class SKlPlayerStateWidget> PlayerStateWidget;

private:
	// Get screen size
	FVector2D GetViewportSize() const;

private:
	// DPI Setting
	TAttribute<float> UIScaler;
};
