// Fill out your copyright notice in the Description page of Project Settings.

#include "SKlGameHUDWidget.h"
#include "SlateOptMacros.h"
#include "SKlShotcutWidget.h"
#include "SDPIScaler.h"
#include "SOverlay.h"
#include "SKlRayInfoWidget.h"
#include "Engine.h"
#include "Engine/Engine.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SKlGameHUDWidget::Construct(const FArguments& InArgs)
{
	UIScaler.Bind(this, &SKlGameHUDWidget::GetUIScaler);

	ChildSlot
	[
		SNew(SDPIScaler)
		.DPIScale(UIScaler)
		[
			SNew(SOverlay)
			+SOverlay::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Bottom)
			[
				SAssignNew(ShotcutWidget, SKlShotcutWidget)
			]
			+SOverlay::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Top)
			[
				SAssignNew(RayInfoWidget, SKlRayInfoWidget)
			]
		]
	];
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
float SKlGameHUDWidget::GetUIScaler() const
{
	return GetViewportSize().Y / 1080.f;
}

FVector2D SKlGameHUDWidget::GetViewportSize() const
{
	FVector2D Result(1920.f, 1080.f);

	if (GEngine && GEngine->GameViewport)
	{
		GEngine->GameViewport->GetViewportSize(Result);
	}

	return Result;
}
