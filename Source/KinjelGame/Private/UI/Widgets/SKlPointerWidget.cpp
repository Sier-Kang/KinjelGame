// Fill out your copyright notice in the Description page of Project Settings.

#include "SKlPointerWidget.h"
#include "SlateOptMacros.h"
#include "UI/Style/KlStyle.h"
#include "UI/Style/KlGameWidgetStyle.h"
#include "SBox.h"
#include "SImage.h"
#include "SButton.h"
#include "ConstructorHelpers.h"
#include "Materials/MaterialInstance.h"
#include "Materials/MaterialInstanceDynamic.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SKlPointerWidget::Construct(const FArguments& InArgs)
{
	GameStyle = &KlStyle::Get().GetWidgetStyle<FKlGameStyle>("BPKlGameStyle");

	CurrentSize = 100.f;

	ChildSlot
	[
		SAssignNew(RootBox, SBox)
		.WidthOverride(TAttribute<FOptionalSize>(this, &SKlPointerWidget::GetBoxWidth))
		.HeightOverride(TAttribute<FOptionalSize>(this, &SKlPointerWidget::GetBoxHeight))
		[
			SNew(SImage)
			.Image(&GameStyle->PointerBrush)
		]
	];

	// Load material inst
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> StaticPointerMaterialInstance(
		TEXT("MaterialInstanceConstant'/Game/Material/PointerMat_Inst.PointerMat_Inst'")
	);

	PointerMaterial = (UMaterialInstanceDynamic*)StaticPointerMaterialInstance.Object;
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

FOptionalSize SKlPointerWidget::GetBoxWidth() const
{
	return FOptionalSize(CurrentSize);
}

FOptionalSize SKlPointerWidget::GetBoxHeight() const
{
	return FOptionalSize(CurrentSize);
}
