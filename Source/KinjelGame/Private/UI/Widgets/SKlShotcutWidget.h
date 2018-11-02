// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class SKlShotcutWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SKlShotcutWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;

private:
	/**
	* Initialize shotcut object container
	*/
	void InitializeContainer();

private:
	/** Get the style of menu */
	const struct FKlGameStyle* GameStyle;

	/** Shotcut object info */
	TSharedPtr<class STextBlock> ShotcutInfo;

	/** Grid Panel Container */
	TSharedPtr<class SUniformGridPanel> GridPanel;

	/** Initialize container in first frame */
	bool bInitializeContainer;
};
