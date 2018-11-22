// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SlateBasics.h"
#include "Widgets/SCompoundWidget.h"

struct ChatShowItem;

class SVerticalBox;

/**
 * 
 */
class SKlChatShowWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SKlChatShowWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;

	/** Add message */
	void AddMessage(FText NewName, FText NewContent);

private:
	void InitializeItem();

private:
	/** Game Style */
	const struct FKlGameStyle* GameStyle;

	TSharedPtr<SVerticalBox> ChatBox;

	/** Items that already activity */
	TArray<TSharedPtr<ChatShowItem>> ActiveList;

	/** Items that un-activity */
	TArray<TSharedPtr<ChatShowItem>> UnActiveList;
};
