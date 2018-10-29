// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Data/FKlTypes.h"

class STextComboBox;

/**
 * 
 */
class SKlChooseRecordWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SKlChooseRecordWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	/**
	* Update record name
	*/
	void UpdateRecordName();

private:
	/** Get the style of menu */
	const struct FKlMenuStyle* MenuStyle;

	// New record name.
	TSharedPtr<STextComboBox> TextComboBox;

	// Record list in combo box.
	TArray<TSharedPtr<FString>> OptionSource;
};
