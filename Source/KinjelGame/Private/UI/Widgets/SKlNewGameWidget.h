// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Data/FKlTypes.h"

class SEditableTextBox;

/**
 * 
 */
class SKlNewGameWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SKlNewGameWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	bool AllowEnterGame();

private:
	/** Get the style of menu */
	const struct FKlMenuStyle* MenuStyle;

	TSharedPtr<SEditableTextBox> EditableTextBox;
};
