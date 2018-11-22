// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SlateBasics.h"
#include "Widgets/SCompoundWidget.h"

struct ChatMessItem;

DECLARE_DELEGATE_TwoParams(FPushMessage, FText, FText)

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
	
	/** Submit event */
	void SubmitEvent(const FText& SubmitText, ETextCommit::Type CommitType);

	/** Send button  trigger event */
	FReply SendEvent();

	/** Add message event */
	void AddMessage(FText NewName, FText NewContent);

	void ScrollToEnd();

public:
	FPushMessage PushMessage;

private:
	/** Game Style */
	const struct FKlGameStyle *GameStyle;

	/** Scroll control */
	TSharedPtr<class SScrollBox> ScrollBox;

	/** Edit text control */
	TSharedPtr<class SEditableTextBox> EditTextBox;

	/** Message list */
	TArray<TSharedPtr<ChatMessItem>> MessageList;
};
