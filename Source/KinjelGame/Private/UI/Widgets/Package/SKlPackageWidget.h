// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SlateBasics.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class SKlPackageWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SKlPackageWidget)
	{}

	SLATE_ATTRIBUTE(float, UIScaler)

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;

	/** Override OnPaint Function */
	virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;

	/** Override OnMouseButtonDown Function */
	virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;

	/*
	* Register Package Manager Event, called by InitPackageManager Delegate in player character
	*/
	void InitPackageManager();
private:
	/** Game style */
	const struct FKlGameStyle* GameStyle;

	/** Shortcut Gird */
	TSharedPtr<class SUniformGridPanel> ShortcutGrid;

	/** Package Grid */
	TSharedPtr<SUniformGridPanel> PackageGrid;

	/** Compositor Gird */
	TSharedPtr<SUniformGridPanel> CompoundGrid;

	/** Output container */
	TSharedPtr<class SBorder> OutputBorder;

	/** Mouse position */
	FVector2D MousePosition;

	/**DPI Scaler */
	TAttribute<float> UIScaler;

	/** Package Manager already initialized flag */
	bool bInitPackageMgr;
};
