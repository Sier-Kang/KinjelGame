// Fill out your copyright notice in the Description page of Project Settings.

#include "SKlContainerShortcutWidget.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SKlContainerShortcutWidget::Construct(const FArguments& InArgs)
{
	SKlContainerBaseWidget::Construct(
		SKlContainerBaseWidget::FArguments()
		.WorkIndex(InArgs._WorkIndex)
	);
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SKlContainerShortcutWidget::ResetContainerPara(int ObjectID, int Num)
{
	bool IsChanged = false;
	if (ObjectIndex != ObjectID || ObjectNum != Num) IsChanged = true;

	SKlContainerBaseWidget::ResetContainerPara(ObjectID, Num);

	if (IsChanged) PackShortChange.ExecuteIfBound(WorkIndex.Get(), ObjectID, Num);
}
