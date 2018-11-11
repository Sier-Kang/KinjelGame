// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SlateBasics.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class SKlPlayerStateWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SKlPlayerStateWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	/**
	* Update player state
	*/
	void UpdateStateWidget(float HPValue, float HungerValue);

private:
	/** Game style */
	const struct FKlGameStyle* GameStyle;

	/** HP Bar*/
	TSharedPtr<class SProgressBar> HPBar;

	/** Hungry Bar */
	TSharedPtr<SProgressBar> HungerBar;
};
