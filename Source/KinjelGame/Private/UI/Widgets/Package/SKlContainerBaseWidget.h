// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SlateBasics.h"
#include "Widgets/SCompoundWidget.h"
#include "Data/FKlTypes.h"

/** Composite Input Delegate */
DECLARE_DELEGATE(FCompoundInput)

/**
* Composite Output Delegate
* @param Object ID
* @param Object Quantity
*/
DECLARE_DELEGATE_TwoParams(FCompoundOutput, int, int)

/**
* @param Object ID
* @param Object Quantity
*/
DECLARE_DELEGATE_TwoParams(FThrowObject, int, int)

/**
* Game change cause by Package shortcut update state Delegate
* @param Shortcut ID
* @param Update Object ID
* @param Update Object Quantity
*/
DECLARE_DELEGATE_ThreeParams(FPackShortChange, int, int, int)

/**
 * 
 */
class SKlContainerBaseWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SKlContainerBaseWidget)
	{}

	SLATE_ATTRIBUTE(int, WorkIndex)

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	/**
	* Get Instance
	*/
	static TSharedPtr<SKlContainerBaseWidget> CreateContainer(EContainerType::Type NeedType, int WorkID);

public:
	/** Compositor Input Delegate */
	FCompoundInput CompoundInput;

	/** Compositor Output Delegate */
	FCompoundOutput CompoundOutput;

	/** Throwed Object Delegate */
	FThrowObject ThrowObject;

	/** Shortcut Updated Delegate */
	FPackShortChange PackShortChange;

protected:
	/** Get Game Style */
	const struct FKlGameStyle* GameStyle;

	/** Attribute of Work Index */
	TAttribute<int> WorkIndex;

	/** Components of container */
	TSharedPtr<class SBorder> ContainerBorder;

	TSharedPtr<SBorder> ObjectImage;

	TSharedPtr<class STextBlock> ObjectNumText;

	/** Hover Flag */
	bool IsHover;

	/** Object ID */
	int ObjectIndex;

	/** Object quantity */
	int ObjectNum;
};
