// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Data/FKlTypes.h"

DECLARE_DELEGATE_OneParam(FOnItemClicked, const EMenuItem::Type)

/**
 * 
 */
class SKlMenuItemWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SKlMenuItemWidget)
	{}

	SLATE_ATTRIBUTE(FText, ItemText)

	SLATE_ATTRIBUTE(EMenuItem::Type, ItemType)

	SLATE_EVENT(FOnItemClicked, OnClicked)

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	/** Override OnMouseButtonDown */
	virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;

	/** Override OnMouseButtonUp */
	virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;

	/** Override OnMouseLeave */
	virtual void OnMouseLeave(const FPointerEvent& MouseEvent) override;

private:
	/**  
	* Get tint color to blend with item's image that can show button down effect
	* @param
	* @return Slate color
	*/
	FSlateColor GetTintColor() const;

private:
	/** Get the style of menu */
	const struct FKlMenuStyle* MenuStyle;

	/**  Clicked Event Delegate */
	FOnItemClicked OnClicked;

	/** Item Type */
	EMenuItem::Type ItemType;

	/** Mouse button down in current item */
	bool bIsMouseButtonDown;
};
