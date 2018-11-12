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
class SKlChatRoomWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SKlChatRoomWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;

	/**
	* Add chat message
	*/
	void AddMessage(FText NewName, FText NewContent);

private:
	/**
	* Initialize content in chat room widget
	*/
	void InitializeItem();

private:
	/** Game style */
	const struct FKlGameStyle* GameStyle;

	TSharedPtr<SVerticalBox> ChatBox;

	// Actived Items
	TArray<TSharedPtr<ChatShowItem>> ActiveList;

	// Unactived items
	TArray<TSharedPtr<ChatShowItem>> UnActiveList;
};
