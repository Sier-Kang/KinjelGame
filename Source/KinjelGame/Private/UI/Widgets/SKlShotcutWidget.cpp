// Fill out your copyright notice in the Description page of Project Settings.

#include "SKlShotcutWidget.h"
#include "SlateOptMacros.h"
#include "UI/Style/KlStyle.h"
#include "UI/Style/KlGameWidgetStyle.h"
#include "SBox.h"
#include "SOverlay.h"
#include "STextBlock.h"
#include "SUniformGridPanel.h"
#include "SBorder.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SKlShotcutWidget::Construct(const FArguments& InArgs)
{
	GameStyle = &KlStyle::Get().GetWidgetStyle<FKlGameStyle>("BPKlGameStyle");

	ChildSlot
	[
		SNew(SBox)
		.WidthOverride(900.f)
		.HeightOverride(160.f)
		[	
			SNew(SOverlay)
			// Shotcut object info 
			+SOverlay::Slot() 
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Top)
			[
				SAssignNew(ShotcutInfo, STextBlock)
				.Font(GameStyle->Font_Outline_40)
				.ColorAndOpacity(GameStyle->FontColor_White)
			]
			// Shotcut container
			+SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(FMargin(0.f, 60.f, 0.f, 0.f))
			[
				SAssignNew(GridPanel, SUniformGridPanel)
				//SNew(SBox)
			]
		]
	];

	bInitializeContainer = false;
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SKlShotcutWidget::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	if (!bInitializeContainer)
	{
		InitializeContainer();

		bInitializeContainer = true;
	}
}

void SKlShotcutWidget::InitializeContainer()
{
	for (int i = 0; i < 9; i++) {
		// Create container
		TSharedPtr<SBorder> Container;
		TSharedPtr<SBorder> ObjectImage;
		TSharedPtr<STextBlock> ObjectNumText;

		SAssignNew(Container, SBorder)
		.BorderImage(&GameStyle->NormalContainerBrush)
		.Padding(FMargin(10.f))
		[
			SAssignNew(ObjectImage, SBorder)
			.BorderImage(&GameStyle->EmptyBrush)
			.HAlign(HAlign_Right)
			.VAlign(VAlign_Bottom)
			.Padding(FMargin(0.f, 0.f, 5.0f, 0))
			[
				SAssignNew(ObjectNumText, STextBlock)
				.Text(FText::FromString("12"))
				.Font(GameStyle->Font_Outline_20)
				.ColorAndOpacity(GameStyle->FontColor_White)
			]
		];

		GridPanel->AddSlot(i, 0)
		[
			Container->AsShared()
		];
	}
}
