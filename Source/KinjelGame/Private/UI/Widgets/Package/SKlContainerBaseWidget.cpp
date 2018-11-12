// Fill out your copyright notice in the Description page of Project Settings.

#include "SKlContainerBaseWidget.h"
#include "SlateOptMacros.h"
#include "UI/Style/KlStyle.h"
#include "UI/Style/KlGameWidgetStyle.h"

#include "SKlContainerOutputWidget.h"
#include "SKlContainerInputWidget.h"
#include "SKlContainerNormalWidget.h"
#include "SKlContainerShortcutWidget.h"

#include "SBorder.h"
#include "STextBlock.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SKlContainerBaseWidget::Construct(const FArguments& InArgs)
{
	// Get Game Style
	GameStyle = &KlStyle::Get().GetWidgetStyle<FKlGameStyle>("BPKlGameStyle");

	// Get Work ID
	WorkIndex = InArgs._WorkIndex;
	
	ChildSlot
	[
		SAssignNew(ContainerBorder, SBorder)
		.BorderImage(&GameStyle->NormalContainerBrush)
		.Padding(FMargin(8.f))
		[
			SAssignNew(ObjectImage, SBorder)
			.BorderImage(&GameStyle->EmptyBrush)
			.HAlign(HAlign_Right)
			.VAlign(VAlign_Bottom)
			.Padding(FMargin(0.f, 0.f, 4.f, 0.f))
			[
				SAssignNew(ObjectNumText, STextBlock)
				.Font(GameStyle->Font_Outline_16)
				.ColorAndOpacity(GameStyle->FontColor_Black)
			]
		]
	];

	IsHover = false;

	// Initialize ObjectIndex and quantity to 0
	ObjectIndex = ObjectNum = 0;
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

TSharedPtr<SKlContainerBaseWidget> SKlContainerBaseWidget::CreateContainer(EContainerType::Type NeedType, int WorkID)
{
	TSharedPtr<SKlContainerBaseWidget> ResultContainer;
	//switch (NeedType)
	//{
	//case EContainerType::Output:
	//	SAssignNew(ResultContainer, SKlContainerOutputWidget).WorkIndex(WorkID);
	//	break;
	//case EContainerType::Input:
	//	SAssignNew(ResultContainer, SKlContainerInputWidget).WorkIndex(WorkID);
	//	break;
	//case EContainerType::Normal:
	//	SAssignNew(ResultContainer, SKlContainerNormalWidget).WorkIndex(WorkID);
	//	break;
	//case EContainerType::Shortcut:
	//	SAssignNew(ResultContainer, SKlContainerShortcutWidget).WorkIndex(WorkID);
	//	break;
	//}

	return ResultContainer;
}
