// Fill out your copyright notice in the Description page of Project Settings.

#include "SKlMenuItemWidget.h"
#include "SlateOptMacros.h"
#include "UI/Style/KlStyle.h"
#include "UI/Style/KlMenuWidgetStyle.h"
#include "SBox.h"
#include "SUserWidget.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SKlMenuItemWidget::Construct(const FArguments& InArgs)
{
	OnClicked = InArgs._OnClicked;
	ItemType = InArgs._ItemType.Get();

	// Get Style of the editor
	MenuStyle = &KlStyle::Get().GetWidgetStyle<FKlMenuStyle>("BPKlMenuStyle");

	ChildSlot
	[
		SNew(SBox)
		.WidthOverride(500.f)
		.HeightOverride(100.f)
		[
			SNew(SOverlay)
			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SImage)
				.Image(&MenuStyle->MenuItemBrush)
				.ColorAndOpacity(this, &SKlMenuItemWidget::GetTintColor)
			]
			+ SOverlay::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(InArgs._ItemText)
				.Font(MenuStyle->Font_60)
			]
		]
	];

	bIsMouseButtonDown = false;
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

FReply SKlMenuItemWidget::OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) 
{
	bIsMouseButtonDown = true;

	return FReply::Handled();
}

FReply SKlMenuItemWidget::OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) 
{
	// if the button is clicked & OnClicked is bound
	if (bIsMouseButtonDown)
	{
		bIsMouseButtonDown = false;

		OnClicked.ExecuteIfBound(ItemType);
	}

	return FReply::Handled();
}

void SKlMenuItemWidget::OnMouseLeave(const FPointerEvent& MouseEvent) 
{
	bIsMouseButtonDown = false;
}

FSlateColor SKlMenuItemWidget::GetTintColor() const 
{
	if (bIsMouseButtonDown)
	{
		return FLinearColor(1.f, 0.1f, 0.1f, 0.5f);
	}

	return FLinearColor(1.f, 1.f, 1.f, 1.f);
}
