// Fill out your copyright notice in the Description page of Project Settings.

#include "SKlMenuHUDWidget.h"
#include "SlateOptMacros.h"
#include "SButton.h"
#include "SImage.h"
#include "UI/Style/KlStyle.h"
#include "UI/Style/KlMenuWidgetStyle.h"
#include "SDPIScaler.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SKlMenuHUDWidget::Construct(const FArguments& InArgs) {
	// Get Style of the editor
	MenuStyle = &KlStyle::Get().GetWidgetStyle<FKlMenuStyle>("BPKlMenuStyle");

	// Bind principle method of UI Scaler
	UIScaler.Bind(this, &SKlMenuHUDWidget::GetUIScaler);

	ChildSlot
	[
		SNew(SDPIScaler)
		.DPIScale(UIScaler)
		[
			SNew(SOverlay)
			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(FMargin(0))
			[
				SNew(SImage)
				.Image(&MenuStyle->MenuHUDBackgroundBrush)
			]
			+ SOverlay::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			.Expose(ImageSlot)
			[
				SNew(SImage)
				.Image(&MenuStyle->MenuBackgroundBrush)
			]
			+ SOverlay::Slot()
			.HAlign(HAlign_Left)
			.VAlign(VAlign_Top)
			[
				SNew(SButton)
				.OnClicked(this, &SKlMenuHUDWidget::OnClicked_Btn)
			]
		]

	];
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

float SKlMenuHUDWidget::GetUIScaler() const 
{
	return GetViewportSize().Y / 1050.0f;
}

FVector2D SKlMenuHUDWidget::GetViewportSize() const
{
	FVector2D Result(1600, 1050);
	if (GEngine && GEngine->GameViewport)
	{
		GEngine->GameViewport->GetViewportSize(Result);
	}

	return Result;
}

FReply SKlMenuHUDWidget::OnClicked_Btn() 
{
	return FReply::Handled();
}
