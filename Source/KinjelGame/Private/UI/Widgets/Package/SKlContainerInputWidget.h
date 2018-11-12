// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SlateBasics.h"
#include "SKlContainerBaseWidget.h"

/**
 * 
 */
class SKlContainerInputWidget : public SKlContainerBaseWidget
{
public:
	SLATE_BEGIN_ARGS(SKlContainerInputWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
};
