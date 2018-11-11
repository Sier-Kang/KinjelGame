// Fill out your copyright notice in the Description page of Project Settings.

#include "SKlPlayerStateWidget.h"
#include "SlateOptMacros.h"
#include "UI/Style/KlStyle.h"
#include "UI/Style/KlGameWidgetStyle.h"
#include "SOverlay.h"
#include "SBox.h"
#include "SConstraintCanvas.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SKlPlayerStateWidget::Construct(const FArguments& InArgs)
{
	GameStyle = &KlStyle::Get().GetWidgetStyle<FKlGameStyle>("BPKlGameStyle");

	ChildSlot
	[
		SNew(SBox)
		.WidthOverride(744.f)
		.HeightOverride(244.f)
		[
			SNew(SOverlay)
			// Background of the widget
			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SImage)
				.Image(&GameStyle->PlayerStateBGBrush)
			]

			// CanvasPanel's progress bar
			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[

				SNew(SConstraintCanvas)
				// HP Bar
				+ SConstraintCanvas::Slot()
				.Anchors(FAnchors(0.f))// Set anchor in left-top
				.Offset(FMargin(442.3f, 90.f, 418.f, 42.f))
				[
					SAssignNew(HPBar, SProgressBar)
					.BackgroundImage(&GameStyle->EmptyBrush)
					.FillImage(&GameStyle->HPBrush)
					.FillColorAndOpacity(FSlateColor(FLinearColor(1.f, 1.f, 1.f, 1.f)))
					.Percent(1.f)
				]

				// Hungry Bar
				+ SConstraintCanvas::Slot()
				.Anchors(FAnchors(0.f))
				.Offset(FMargin(397.5f, 145.f, 317.f, 26.f))
				[
					SAssignNew(HungerBar, SProgressBar)
					.BackgroundImage(&GameStyle->EmptyBrush)
					.FillImage(&GameStyle->HungerBrush)
					.FillColorAndOpacity(FSlateColor(FLinearColor(1.f, 1.f, 1.f, 1.f)))
					.Percent(1.f)
				]
			]

			// Character's head image and its background
			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(FMargin(0.f, 0.f, 500.f, 0.f))
			[
				SNew(SOverlay)

				+ SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				[
					SNew(SImage)
					.Image(&GameStyle->PlayerHeadBGBrush)
				]

				+ SOverlay::Slot()
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Center)
				[
					SNew(SImage)
					.Image(&GameStyle->PlayerHeadBrush)
				]
			]
		]
	];
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SKlPlayerStateWidget::UpdateStateWidget(float HPValue, float HungerValue)
{
	if (HPValue > 0) 
		HPBar->SetPercent(FMath::Clamp<float>(HPValue, 0.f, 1.f));

	if (HungerValue > 0) 
		HungerBar->SetPercent(FMath::Clamp<float>(HungerValue, 0.f, 1.f));
}
