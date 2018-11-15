// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SlateBasics.h"
#include "SKlContainerBaseWidget.h"

/**
 * 
 */
class SKlContainerShortcutWidget : public SKlContainerBaseWidget
{
public:
	SLATE_BEGIN_ARGS(SKlContainerShortcutWidget)
	{}

	SLATE_ATTRIBUTE(int, WorkIndex)

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	/**
	* Reset container parameters override
	*/
	virtual void ResetContainerPara(int ObjectID, int Num) override;
};
