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
#include "Data/FKlDataHandle.h"

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
	switch (NeedType)
	{
	case EContainerType::Output:
		SAssignNew(ResultContainer, SKlContainerOutputWidget).WorkIndex(WorkID);
		break;
	case EContainerType::Input:
		SAssignNew(ResultContainer, SKlContainerInputWidget).WorkIndex(WorkID);
		break;
	case EContainerType::Normal:
		SAssignNew(ResultContainer, SKlContainerNormalWidget).WorkIndex(WorkID);
		break;
	case EContainerType::Shortcut:
		SAssignNew(ResultContainer, SKlContainerShortcutWidget).WorkIndex(WorkID);
		break;
	}

	return ResultContainer;
}

void SKlContainerBaseWidget::UpdateHovered(bool IsHovered)
{
	if (IsHovered)
	{
		// If already hovered in previous frame
		if (!IsHover) 
			ContainerBorder->SetBorderImage(&GameStyle->ChoosedContainerBrush);
	}
	else
	{
		if (IsHover) 
			ContainerBorder->SetBorderImage(&GameStyle->NormalContainerBrush);
	}

	IsHover = IsHovered;
}

void SKlContainerBaseWidget::ResetContainerPara(int ObjectID, int Num)
{
	// Update tex if ID isn't same
	if (ObjectIndex != ObjectID) ObjectImage->SetBorderImage(FKlDataHandle::Get()->ObjectBrushList[ObjectID]);

	ObjectIndex = ObjectID;
	ObjectNum = Num;

	if (ObjectIndex == 0) {
		ObjectNumText->SetText(FText::FromString(""));
	}
	else
	{
		if (MultiplyAble(ObjectIndex)) {
			ObjectNumText->SetText(FText::FromString(FString::FromInt(ObjectNum)));
		}
		else
		{
			ObjectNumText->SetText(FText::FromString(""));
		}
	}
}

int SKlContainerBaseWidget::GetIndex() const
{
	return ObjectIndex;
}

int SKlContainerBaseWidget::GetNum() const
{
	return ObjectNum;
}

void SKlContainerBaseWidget::LeftOperate(int InputID, int InputNum, int& OutputID, int& OutputNum)
{
	// Input object is the same with object in current container
	if (InputID == ObjectIndex && MultiplyAble(ObjectIndex))
	{
		OutputID = (ObjectNum + InputNum <= 64) ? 0 : InputID;

		OutputNum = (ObjectNum + InputNum <= 64) ? 0 : (ObjectNum + InputNum - 64);

		ObjectNum = (ObjectNum + InputNum <= 64) ? (ObjectNum + InputNum) : 64;

		ResetContainerPara(ObjectIndex, ObjectNum);

		return;
	}

	OutputID = ObjectIndex;

	ResetContainerPara(InputID, InputNum);
}

void SKlContainerBaseWidget::RightOperate(int InputID, int InputNum, int& OutputID, int& OutputNum)
{
	// No dragged object.
	if (InputID == 0)
	{
		OutputID = ObjectIndex;

		OutputNum = (ObjectNum % 2 == 1) ? (ObjectNum / 2 + 1) : (ObjectNum / 2);

		ResetContainerPara(ObjectNum - OutputNum == 0 ? 0 : ObjectIndex, ObjectNum - OutputNum);

		return;
	}

	// Container is empty, and dragged object
	if (ObjectIndex == 0 || (InputID == ObjectIndex && MultiplyAble(InputID)))
	{
		OutputNum = (ObjectNum + 1 <= 64) ? (InputNum - 1) : InputNum;

		OutputID = (OutputNum == 0) ? 0 : InputID;

		ResetContainerPara(InputID, (ObjectNum + 1 <= 64) ? (ObjectNum + 1) : ObjectNum);

		return;
	}

	OutputID = ObjectIndex;
	OutputNum = ObjectNum;

	ResetContainerPara(InputID, InputNum);
}

bool SKlContainerBaseWidget::IsEmpty()
{
	return ObjectIndex == 0;
}

bool SKlContainerBaseWidget::RemainSpace(int ObjectID)
{
	if (ObjectIndex == ObjectID && ObjectNum < 64 && MultiplyAble(ObjectIndex)) 
		return true;

	return false;
}

void SKlContainerBaseWidget::AddObject(int ObjectID)
{
	if (ObjectIndex == 0)
	{
		ResetContainerPara(ObjectID, 1);
		return;
	}

	if (ObjectIndex == ObjectID && ObjectNum < 64 && MultiplyAble(ObjectIndex)) {
		ResetContainerPara(ObjectIndex, ObjectNum + 1);
	}
}

bool SKlContainerBaseWidget::MultiplyAble(int ObjectID)
{
	// Get object attribute
	TSharedPtr<ObjectAttribute> ObjectAttr = *FKlDataHandle::Get()->ObjectAttrMap.Find(ObjectID);

	return (ObjectAttr->ObjectType != EObjectType::Tool && ObjectAttr->ObjectType != EObjectType::Weapon);
}
