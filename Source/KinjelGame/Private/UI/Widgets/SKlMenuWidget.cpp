// Fill out your copyright notice in the Description page of Project Settings.

#include "SKlMenuWidget.h"

#include "UI/Style/KlStyle.h"
#include "UI/Style/KlMenuWidgetStyle.h"
#include "SKlMenuItemWidget.h"
#include "SKlNewGameWidget.h"
#include "SKlChooseRecordWidget.h"
#include "SKlGameOptionWidget.h"

#include "Common/FKlHelper.h"
#include "Data/FKlDataHandle.h"

#include "SlateOptMacros.h"
#include "SImage.h"
#include "SOverlay.h"
#include "VerticalBox.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SKlMenuWidget::Construct(const FArguments& InArgs) {
	// Get Style of the editor
	MenuStyle = &KlStyle::Get().GetWidgetStyle<FKlMenuStyle>("BPKlMenuStyle");

	ChildSlot
		[
			SAssignNew(RootSizeBox, SBox)
			[
				SNew(SOverlay)
				+ SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.Padding(FMargin(0.f, 50.f, 0.f, 0.f))
				[
					SNew(SImage)
					.Image(&MenuStyle->MenuBackgroundBrush)
				]
				+ SOverlay::Slot()
				.HAlign(HAlign_Left)
				.VAlign(VAlign_Center)
				.Padding(FMargin(0.f, 25.f, 0.f, 0.f))
				[
					SNew(SImage)
					.Image(&MenuStyle->LeftIconBrush)
				]
				+ SOverlay::Slot()
				.HAlign(HAlign_Right)
				.VAlign(VAlign_Center)
				.Padding(FMargin(0.f, 25.f, 0.f, 0.f))
				[
					SNew(SImage)
					.Image(&MenuStyle->RightIconBrush)
				]
				+ SOverlay::Slot()
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Top)
				[
					SNew(SBox)
					.WidthOverride(400.f)
					.HeightOverride(100.f)
					[
						SNew(SBorder)
						.BorderImage(&MenuStyle->TitleBorderBrush)
						.HAlign(HAlign_Center)
						.VAlign(VAlign_Center)
						[
							SAssignNew(TitleText, STextBlock)
							.Font(KlStyle::Get().GetFontStyle("MenuItemFont"))
							.Text(NSLOCTEXT("KlMenu", "Menu", "Menu"))
						]
					]
				]
				+SOverlay::Slot()
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Top)
				.Padding(FMargin(0.f, 130.f, 0.f, 0.f))
				[
					SAssignNew(ContentBox, SVerticalBox)
				]
			]
		];

	RootSizeBox->SetWidthOverride(600.f);
	RootSizeBox->SetHeightOverride(510.f);

	ContentBox->AddSlot()
		[
			SNew(SKlChooseRecordWidget)
		];
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SKlMenuWidget::MenuItemOnClicked(EMenuItem::Type ItemType) 
{
	FKlHelper::Debug(FString("Menu Item On Clicked."), 10.f);
}

void SKlMenuWidget::ChangeCulture(ECultureTeam Culture)
{
	FKlDataHandle::Get()->ChangeLocalizationCulture(Culture);
}

void SKlMenuWidget::ChangeVolume(const float MusicVolume, const float SoundVolume)
{
	FKlDataHandle::Get()->ResetMenuVolume(MusicVolume, SoundVolume);
}
