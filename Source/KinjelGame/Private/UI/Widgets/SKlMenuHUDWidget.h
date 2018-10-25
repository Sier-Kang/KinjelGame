// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SOverlay.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class SKlMenuHUDWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SKlMenuHUDWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

private:
	/**
	* UI Scaler principle method
	* @param Comment
	* @return Comment
	*/
	float GetUIScaler() const;

	/** 
	* Get viewport size 
	* @param Comment
	* @return Viewport size
	*/
	FVector2D GetViewportSize() const;

private:
	/** Get the style of menu */
	const struct FKlMenuStyle* MenuStyle;

	/** DPI scale coefficients */
	TAttribute<float> UIScaler;

	/** Menu Widget Ptr*/
	TSharedPtr<class SKlMenuWidget> MenuWidget;
};
