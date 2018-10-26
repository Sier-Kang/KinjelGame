// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Data/FKlTypes.h"

/**
 * 
 */
class SKlMenuWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SKlMenuWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

private:
	/**
	* Item click event.
	* @params Item type
	* @return
	*/
	void MenuItemOnClicked(EMenuItem::Type ItemType);

private:
	/** Size box of the menu */
	TSharedPtr<SBox> RootSizeBox;

	/** Title Text */
	TSharedPtr<STextBlock> TitleText;

	/** Get the style of menu */
	const struct FKlMenuStyle* MenuStyle;

	/** To save vertical list */
	TSharedPtr<SVerticalBox> ContentBox;
};
