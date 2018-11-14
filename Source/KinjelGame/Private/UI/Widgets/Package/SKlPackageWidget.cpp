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
#include "Data/FKlDataHandle.h"

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

	if (!bInitPackageMgr) return LayerId;

	// If Object number is not 0 in Package Manager, then rendering
	if (GetVisibility() == EVisibility::Visible && KlPackageManager::Get()->ObjectIndex != 0 && KlPackageManager::Get()->ObjectNum != 0)
	{
		// Render object icon
		FSlateDrawElement::MakeBox(
			OutDrawElements,
			LayerId + 30,
			AllottedGeometry.ToPaintGeometry(MousePosition - FVector2D(32.f, 32.f), FVector2D(64.f, 64.f)),
			FKlDataHandle::Get()->ObjectBrushList[KlPackageManager::Get()->ObjectIndex],
			ESlateDrawEffect::None,
			FLinearColor(1.f, 1.f, 1.f, 1.f)
		);


		// Get object attribute
		TSharedPtr<ObjectAttribute> ObjectAttr = *FKlDataHandle::Get()->ObjectAttrMap.Find(KlPackageManager::Get()->ObjectIndex);
		// Render number, if it is not addable nor render
		if (ObjectAttr->ObjectType != EObjectType::Tool && ObjectAttr->ObjectType != EObjectType::Weapon) {
			// Render "Num" Text
			FSlateDrawElement::MakeText(
				OutDrawElements,
				LayerId + 30,
				AllottedGeometry.ToPaintGeometry(MousePosition + FVector2D(12.f, 16.f), FVector2D(16.f, 16.f)),
				FString::FromInt(KlPackageManager::Get()->ObjectNum),
				GameStyle->Font_Outline_16,
				ESlateDrawEffect::None,
				GameStyle->FontColor_Black
			);
		}

	}

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

	// Initialize Main Shortcut
	for (int i = 0; i < 36; ++i) {
		TSharedPtr<SKlContainerBaseWidget> NewContainer = SKlContainerBaseWidget::CreateContainer(EContainerType::Normal, i);

		PackageGrid->AddSlot(i % 9, i / 9)
		[
			NewContainer->AsShared()
		];

		KlPackageManager::Get()->InsertContainer(NewContainer, EContainerType::Normal);
	}

	// Initialize compound input
	for (int i = 0; i < 9; ++i) {
		TSharedPtr<SKlContainerBaseWidget> NewContainer = SKlContainerBaseWidget::CreateContainer(EContainerType::Input, i);

		CompoundGrid->AddSlot(i % 3, i / 3)
		[
			NewContainer->AsShared()
		];

		KlPackageManager::Get()->InsertContainer(NewContainer, EContainerType::Input);
	}

	// Initialize compound output
	TSharedPtr<SKlContainerBaseWidget> NewContainer = SKlContainerBaseWidget::CreateContainer(EContainerType::Output, 1);

	OutputBorder->SetContent(NewContainer->AsShared());

	KlPackageManager::Get()->InsertContainer(NewContainer, EContainerType::Output);

	bInitPackageMgr = true;
}
