// Fill out your copyright notice in the Description page of Project Settings.

#include "SKlChooseRecordWidget.h"
#include "SlateOptMacros.h"
#include "UI/Style/KlStyle.h"
#include "UI/Style/KlMenuWidgetStyle.h"
#include "Common/FKlHelper.h"
#include "Data/FKlDataHandle.h"

#include "SBox.h"
#include "STextBlock.h"
#include "SOverlay.h"
#include "STextComboBox.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SKlChooseRecordWidget::Construct(const FArguments& InArgs)
{
	// Get Style of the editor
	MenuStyle = &KlStyle::Get().GetWidgetStyle<FKlMenuStyle>("BPKlMenuStyle");

	for (TArray<FString>::TIterator It(FKlDataHandle::Get()->RecordDataList); It; It++) {
		OptionSource.Add(MakeShareable(new FString(*It)));
	}

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
				.Text(NSLOCTEXT("KlMenu", "ChooseRecord", "ChooseRecord"))
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
					SAssignNew(TextComboBox, STextComboBox)
					.Font(MenuStyle->Font_30)
					.OptionsSource(&OptionSource)
				]
			]
		]
	];

	// Set default setting record
	if (OptionSource[0].IsValid())
	{
		TextComboBox->SetSelectedItem(OptionSource[0]);
	}
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SKlChooseRecordWidget::UpdateRecordName()
{
	FKlDataHandle::Get()->RecordName = *TextComboBox->GetSelectedItem().Get();
}
