// Fill out your copyright notice in the Description page of Project Settings.

#include "SKlPackageWidget.h"
#include "SlateOptMacros.h"

#include "UI/Style/KlStyle.h"
#include "UI/Style/KlGameWidgetStyle.h"

#include "SOverlay.h"
#include "SBox.h"
#include "SUniformGridPanel.h"
#include "Engine/Engine.h"
#include "Engine/GameEngine.h"
#include "Engine/GameViewportClient.h"
#include "SKlContainerBaseWidget.h"
#include "Data/FKlTypes.h"
#include "KlPackageManager.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SKlPackageWidget::Construct(const FArguments& InArgs)
{
	GameStyle = &KlStyle::Get().GetWidgetStyle<FKlGameStyle>("BPKlGameStyle");

	UIScaler = InArgs._UIScaler;

	ChildSlot
	[
		SNew(SOverlay)
		// Package
		+SOverlay::Slot()
		.HAlign(HAlign_Right)
		.VAlign(VAlign_Center)
		.Padding(FMargin(0.f, 0.f, 50.f, 0.f))
		[
			SNew(SBox)
			.WidthOverride(800.f)
			.HeightOverride(800.f)
			[
				SNew(SOverlay)
				// Background Image
				+SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				[
					SNew(SImage)
					.Image(&GameStyle->PackageBGBrush)
				]
				// Shortcut in bottom
				+SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.Padding(FMargin(40.f, 680.f, 40.f, 40.f))
				[
					SAssignNew(ShortcutGrid, SUniformGridPanel)
				]
				// Main Package
				+SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.Padding(FMargin(40.f, 320.f, 40.f, 60.f))
				[
					SAssignNew(PackageGrid, SUniformGridPanel)
				]

				// Compositor Input
				+ SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.Padding(FMargin(80.f, 40.f, 480.f, 520.f))
				[
					SAssignNew(CompoundGrid, SUniformGridPanel)
				]

				// Compositor Output
				+ SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.Padding(FMargin(560.f, 120.f, 160.f, 600.f))
				[
					SAssignNew(OutputBorder, SBorder)
				]

				// Compositor Arrow
				+SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.Padding(FMargin(400.f, 120.f, 320.f, 600.f))
				[
					SNew(SImage)
					.Image(&GameStyle->CompoundArrowBrush)
				]
			]
		]
	];

	MousePosition = FVector2D(0.f, 0.f);

	bInitPackageMgr = false;
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SKlPackageWidget::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	// If Package displaying and world exists, update mouse position in real time
	if (GetVisibility() == EVisibility::Visible && GEngine) {
		GEngine->GameViewport->GetMousePosition(MousePosition);
		MousePosition = MousePosition / UIScaler.Get();
	}

	if (bInitPackageMgr) {
		// Update container display real time
		KlPackageManager::Get()->UpdateHovered(MousePosition, AllottedGeometry);
	}
}

int32 SKlPackageWidget::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	SCompoundWidget::OnPaint(Args, AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);

	return LayerId;
}

FReply SKlPackageWidget::OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	return FReply::Handled();
}

void SKlPackageWidget::InitPackageManager()
{
	// Initialize Shortcut 
	for (int i = 0; i < 9; ++i) {
		TSharedPtr<SKlContainerBaseWidget> NewContainer = 
			SKlContainerBaseWidget::CreateContainer(EContainerType::Shortcut, i);

		ShortcutGrid->AddSlot(i, 0)
		[
			NewContainer->AsShared()
		];
		
		// Register container to Package Manager 
		KlPackageManager::Get()->InsertContainer(NewContainer, EContainerType::Shortcut);
	}
}
