// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
	// Get the style of menu
	const struct FKlMenuStyle* MenuStyle;
};