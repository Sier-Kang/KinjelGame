// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SlateBasics.h"
#include "Widgets/SCompoundWidget.h"

DECLARE_DELEGATE_OneParam(FRegisterRayInfoEvent, TSharedPtr<STextBlock>)

/**
 * 
 */
class SKlRayInfoWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SKlRayInfoWidget)
	{
	
	}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;

public:
	FRegisterRayInfoEvent RegisterRayInfoEvent;

private:
	/** Object name that ray cast to */
	TSharedPtr<class STextBlock> RayInfoTextBlock;

	/** Game style */
	const struct FKlGameStyle* GameStyle;

	/** Initialize Ray info event */
	bool bIsInitRayInfoEvent;
};
