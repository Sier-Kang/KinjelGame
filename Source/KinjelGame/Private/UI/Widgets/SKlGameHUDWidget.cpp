// Fill out your copyright notice in the Description page of Project Settings.

#include "SKlGameHUDWidget.h"
#include "SlateOptMacros.h"
#include "SKlShotcutWidget.h"
#include "SDPIScaler.h"
#include "SOverlay.h"
#include "SKlRayInfoWidget.h"
#include "Engine.h"
#include "Engine/Engine.h"
#include "SKlPointerWidget.h"
#include "SKlPlayerStateWidget.h"
#include "Package/SKlPackageWidget.h"
#include "SKlChatRoomWidget.h"
#include "SKlGameMenuWidget.h"

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
			// Shortcut panel
			+SOverlay::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Bottom)
			[
				SAssignNew(ShotcutWidget, SKlShotcutWidget)
			]
			// Ray cast object text
			+SOverlay::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Top)
			[
				SAssignNew(RayInfoWidget, SKlRayInfoWidget)
			]
			// Pointer insight widget
			+SOverlay::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SAssignNew(PointerWidget, SKlPointerWidget)
			]
			// Player state widget
			+SOverlay::Slot()
			.HAlign(HAlign_Left)
			.VAlign(VAlign_Top)
			[
				SAssignNew(PlayerStateWidget, SKlPlayerStateWidget)
			]
			// Black Mask, placed between Event UI and Game UI.
			+SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SAssignNew(BlackShade, SBorder)
				// Set black and transparency
				.ColorAndOpacity(TAttribute<FLinearColor>(FLinearColor(0.2f, 0.2f, 0.2f, 0.5f)))
				.Visibility(EVisibility::Hidden)
				[
					SNew(SImage)
				]
			]
			// Game menu widget
			+SOverlay::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SAssignNew(GameMenuWidget, SKlGameMenuWidget)
				.Visibility(EVisibility::Hidden)
			]
			// Chat Room Widget
			+SOverlay::Slot()
			.HAlign(HAlign_Left)
			.VAlign(VAlign_Bottom)
			[
				SAssignNew(ChatRoomWidget, SKlChatRoomWidget)
				.Visibility(EVisibility::Hidden)
			]
			// Package Widget
			+SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SAssignNew(PackageWidget, SKlPackageWidget)
				.Visibility(EVisibility::Hidden)
				//.UIScaler(UIScaler)
			]
		]
	];

	// Initialize UIMap
	InitUIMap();
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
float SKlGameHUDWidget::GetUIScaler() const
{
	return GetViewportSize().Y / 1080.f;
}

void SKlGameHUDWidget::ShowGameUI(EGameUIType::Type PreUI, EGameUIType::Type NextUI)
{
	// If PreUI's type is Game, then switch to Black Mask
	if (PreUI == EGameUIType::Game)
	{
		BlackShade->SetVisibility(EVisibility::Visible);
	}
	else
	{
		// Hide current showed game ui 
		UIMap.Find(PreUI)->Get()->SetVisibility(EVisibility::Hidden);
	}

	// If NextUI's type is Game, hide Black Mask
	if (NextUI == EGameUIType::Game)
	{
		BlackShade->SetVisibility(EVisibility::Hidden);
	}
	else
	{
		// Show game ui that current consistent to current game ui type
		UIMap.Find(NextUI)->Get()->SetVisibility(EVisibility::Visible);

		//if (NextUI == EGameUIType::ChatRoom) ChatRoomWidget->ScrollToEnd();

		//if (NextUI == EGameUIType::Lose) GameMenuWidget->GameLose();

		//if (NextUI == EGameUIType::Pause) GameMenuWidget->ResetMenu();
	}
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

void SKlGameHUDWidget::InitUIMap()
{
	// Add element to UIMap
	UIMap.Add(EGameUIType::Pause, GameMenuWidget);
	UIMap.Add(EGameUIType::Package, PackageWidget);
	UIMap.Add(EGameUIType::ChatRoom, ChatRoomWidget);
	UIMap.Add(EGameUIType::Lose, GameMenuWidget);

	// Bind delegate
	//ChatRoomWidget->PushMessage.BindRaw(ChatShowWidget.Get(), &SSlAiChatShowWidget::AddMessage);
	// Initialize timer time to 0
	//MessageTimeCount = 0.f;
}
