// Fill out your copyright notice in the Description page of Project Settings.

#include "SKlMenuHUDWidget.h"
#include "SlateOptMacros.h"
#include "SButton.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SKlMenuHUDWidget::Construct(const FArguments& InArgs)
{
	ChildSlot
	[
		SNew(SButton)
	];
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
