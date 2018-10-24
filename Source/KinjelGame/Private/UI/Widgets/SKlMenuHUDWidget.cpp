// Fill out your copyright notice in the Description page of Project Settings.

#include "SKlMenuHUDWidget.h"
#include "SlateOptMacros.h"
#include "SButton.h"
#include "SImage.h"
#include "UI/Style/KlStyle.h"
#include "UI/Style/KlMenuWidgetStyle.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SKlMenuHUDWidget::Construct(const FArguments& InArgs)
{
	// Get Style of the editor
	MenuStyle = &KlStyle::Get().GetWidgetStyle<FKlMenuStyle>("BPKlMenuStyle");

	ChildSlot
		[
			SNew(SImage)
			.Image(&MenuStyle->MenuHUDBackgroundBrush)
	];
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
