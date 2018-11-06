// Fill out your copyright notice in the Description page of Project Settings.

#include "SKlRayInfoWidget.h"
#include "SlateOptMacros.h"
#include "STextBlock.h"
#include "UI/Style/KlStyle.h"
#include "UI/Style/KlGameWidgetStyle.h"
#include "SBox.h"
#include "SBorder.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SKlRayInfoWidget::Construct(const FArguments& InArgs)
{
	GameStyle = &KlStyle::Get().GetWidgetStyle<FKlGameStyle>("BPKlGameStyle");

	bIsInitRayInfoEvent = false;

	ChildSlot
	[
		SNew(SBox)
		.HeightOverride(100)
		.WidthOverride(400)
		[
			SNew(SBorder)
			.BorderImage(&GameStyle->RayInfoBrush)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SAssignNew(RayInfoTextBlock, STextBlock)
				.Font(GameStyle->Font_Outline_50)
				.ColorAndOpacity(GameStyle->FontColor_Black)
			]
		]
	];
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SKlRayInfoWidget::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	if (!bIsInitRayInfoEvent)
	{
		RegisterRayInfoEvent.ExecuteIfBound(RayInfoTextBlock);

		bIsInitRayInfoEvent = true;
	}
}
