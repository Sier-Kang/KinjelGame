// Fill out your copyright notice in the Description page of Project Settings.

#include "SKlChatRoomWidget.h"
#include "SlateOptMacros.h"
#include "UI/Style/KlStyle.h"
#include "UI/Style/KlGameWidgetStyle.h"
#include "SBox.h"
#include "SOverlay.h"
#include "SBoxPanel.h"
#include "SBorder.h"
#include "STextBlock.h"
#include "SMultiLineEditableText.h"

/**
* Item of ChatRoom widget 
*/
struct ChatShowItem
{
	// Transparency
	float Alpha;

	// Horizontal component
	TSharedPtr<SHorizontalBox> CSBox;

	// Name 
	TSharedPtr<STextBlock> CSName;

	// Message content border
	TSharedPtr<SBorder> CSBorder;

	// Message content
	TSharedPtr<SMultiLineEditableText> CSContent;

	// Struct constructor
	ChatShowItem(const FSlateBrush* EmptyBrush, const FSlateFontInfo FontInfo)
	{
		Alpha = 0.f;
		// Instanced component
		SAssignNew(CSBox, SHorizontalBox)

		+ SHorizontalBox::Slot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.AutoWidth()
		[
			SAssignNew(CSName, STextBlock)
			.Font(FontInfo)
			.ColorAndOpacity(FSlateColor(FLinearColor(0.f, 1.f, 0.f, 1.f)))
		]

		+ SHorizontalBox::Slot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.FillWidth(1.f)
		[
			SAssignNew(CSBorder, SBorder)
			.BorderImage(EmptyBrush)
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SAssignNew(CSContent, SMultiLineEditableText)
				.WrappingPolicy(ETextWrappingPolicy::AllowPerCharacterWrapping)
				.AutoWrapText(true)
				.Font(FontInfo)
			]
		];
	}

	// Active component
	TSharedPtr<SHorizontalBox> ActiveItem(FText NewName, FText NewContent)
	{
		CSName->SetText(NewName);
		CSContent->SetText(NewContent);
		Alpha = 1.f;
		CSName->SetColorAndOpacity(FSlateColor(FLinearColor(0.f, 1.f, 0.f, Alpha)));
		CSBorder->SetColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, Alpha));
		return CSBox;
	}

	// Faded, return bActive
	bool DeltaDisappear(float DeltaTime)
	{
		Alpha = FMath::Clamp<float>(Alpha - DeltaTime * 0.05f, 0.f, 1.f);
		CSName->SetColorAndOpacity(FSlateColor(FLinearColor(0.f, 1.f, 0.f, Alpha)));
		CSBorder->SetColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, Alpha));
		if (Alpha == 0.f)
		{
			return true;
		}
		return false;
	}

};

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SKlChatRoomWidget::Construct(const FArguments& InArgs)
{
	//Get GameStyle
	GameStyle = &KlStyle::Get().GetWidgetStyle<FKlGameStyle>("BPKlGameStyle");
	
	ChildSlot
	[
		SNew(SBox)
		.WidthOverride(500.f)
		.HeightOverride(600.f)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Bottom)
		[
			SAssignNew(ChatBox, SVerticalBox)
		]
	];

	// Initialize chat widget items
	InitializeItem();
}

void SKlChatRoomWidget::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	TArray<TSharedPtr<ChatShowItem>> TempList;

	for (TArray<TSharedPtr<ChatShowItem>>::TIterator It(ActiveList); It; ++It)
	{
		if ((*It)->DeltaDisappear(InDeltaTime))
		{
			ChatBox->RemoveSlot((*It)->CSBox->AsShared());

			TempList.Push(*It);
		}
	}

	for (int i = 0; i < TempList.Num(); ++i) {
		ActiveList.Remove(TempList[i]);
		UnActiveList.Push(TempList[i]);
	}
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SKlChatRoomWidget::AddMessage(FText NewName, FText NewContent)
{
	TSharedPtr<ChatShowItem> InsertItem;

	if (UnActiveList.Num() > 0) {
		InsertItem = UnActiveList[0];
		UnActiveList.RemoveAt(0);
	}
	else
	{
		// Get first item in ActvieList
		InsertItem = ActiveList[0];
		ActiveList.RemoveAt(0);

		ChatBox->RemoveSlot(InsertItem->CSBox->AsShared());
	}

	ChatBox->AddSlot()
	.HAlign(HAlign_Fill)
	.VAlign(VAlign_Fill)
	.FillHeight(1.f)
	[
		InsertItem->ActiveItem(NewName, NewContent)->AsShared()
	];

	ActiveList.Push(InsertItem);
}

void SKlChatRoomWidget::InitializeItem()
{
	for (int i = 0; i < 10; ++i) {
		UnActiveList.Add(MakeShareable(new ChatShowItem(&GameStyle->EmptyBrush, GameStyle->Font_16)));
	}
}
