// Fill out your copyright notice in the Description page of Project Settings.

#include "SKlContainerInputWidget.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SKlContainerInputWidget::Construct(const FArguments& InArgs)
{
	SKlContainerBaseWidget::Construct(
		SKlContainerBaseWidget::FArguments()
		.WorkIndex(InArgs._WorkIndex)
	);
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
