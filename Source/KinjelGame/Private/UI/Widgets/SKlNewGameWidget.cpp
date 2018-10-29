// Fill out your copyright notice in the Description page of Project Settings.

#include "SKlNewGameWidget.h"
#include "SlateOptMacros.h"
#include "UI/Style/KlStyle.h"
#include "UI/Style/KlMenuWidgetStyle.h"
#include "Common/FKlHelper.h"
#include "Data/FKlDataHandle.h"

#include "SBox.h"
#include "STextBlock.h"
#include "SOverlay.h"
#include "SEditableTextBox.h"


BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SKlNewGameWidget::Construct(const FArguments& InArgs)
{
	// Get Style of the editor
	MenuStyle = &KlStyle::Get().GetWidgetStyle<FKlMenuStyle>("BPKlMenuStyle");

	ChildSlot
	[
		SNew(SBox)
		.WidthOverride(500.f)
		.HeightOverride(100.f)
		[
			SNew(SOverlay)
			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SImage)
				.Image(&MenuStyle->MenuItemBrush)
			]
			+ SOverlay::Slot()
			.HAlign(HAlign_Left)
			.VAlign(VAlign_Center)
			.Padding(FMargin(20.f, 0.f, 0.f, 0.f))
			[
				SNew(STextBlock)
				.Font(MenuStyle->Font_40)
				.Text(NSLOCTEXT("KlMenu", "NewGame", "NewGame"))
			]
			+ SOverlay::Slot()
			.HAlign(HAlign_Right)
			.VAlign(VAlign_Center)
			.Padding(FMargin(0.f, 0.f, 20.f, 0.f))
			[
				SNew(SBox)
				.WidthOverride(300.f)
				.HeightOverride(60.f)
				[
					SAssignNew(EditableTextBox, SEditableTextBox)
					.HintText(NSLOCTEXT("KlMenu", "RecordNameHint", "Input Record name!"))
					.Font(MenuStyle->Font_30)
				]
			]
		]
	];
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

bool SKlNewGameWidget::AllowEnterGame()
{
	// Get record name
	FText InputText = EditableTextBox->GetText();
	if (InputText.ToString().IsEmpty()) return false;
	
	// Query, if exists same records in history
	for (TArray<FString>::TIterator It(FKlDataHandle::Get()->RecordDataList); It; It++) {
		if ((*It).Equals(InputText.ToString())) {
			// Set TextBox be null
			EditableTextBox->SetText(FText::FromString(""));
			// Update the Hint text - Record already exists!
			EditableTextBox->SetHintText(NSLOCTEXT("KlMenu", "NameRepeatedHint", "Record name Repeated!"));

			return false;
		}
	}
	// Save new record
	FKlDataHandle::Get()->RecordName = InputText.ToString();

	return true;
}
