// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SlateBasics.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class SKlPointerWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SKlPointerWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;

public:
	/**
	* Update Pointer insight
	*/
	void UpdatePointer(bool IsAim, float Range);

private:
	// Set Root box's width and height
	FOptionalSize GetBoxWidth() const;

	FOptionalSize GetBoxHeight() const;

private:
	/** Game style */
	const struct FKlGameStyle* GameStyle;

	TSharedPtr<class SBox> RootBox;

	/** Box size */
	float CurrentSize;

	/** Dynamic material inst */
	class UMaterialInstanceDynamic* PointerMaterial;

	/** Is character aimed at object */
	bool bIsAimed;
};
