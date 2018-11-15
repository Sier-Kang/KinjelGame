// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SlateBasics.h"
#include "SKlContainerBaseWidget.h"

/**
 * 
 */
class SKlContainerOutputWidget : public SKlContainerBaseWidget
{
public:
	SLATE_BEGIN_ARGS(SKlContainerOutputWidget)
	{}

	SLATE_ATTRIBUTE(int, WorkIndex)

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	/**
	* Left operation override
	*/
	virtual void LeftOperate(int InputID, int InputNum, int& OutputID, int& OutputNum) override;

	/**
	* Right operation override
	*/
	virtual void RightOperate(int InputID, int InputNum, int& OutputID, int& OutputNum) override;
};
