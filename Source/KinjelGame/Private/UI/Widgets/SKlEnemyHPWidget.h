// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SlateBasics.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class SKlEnemyHPWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SKlEnemyHPWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	/**
	* Change HP for Enemy Character
	*/
	void ChangeHP(float HP);

private:
	TSharedPtr<class SProgressBar> HPBar;

	/** Color of result */
	FLinearColor ResultColor;
};
