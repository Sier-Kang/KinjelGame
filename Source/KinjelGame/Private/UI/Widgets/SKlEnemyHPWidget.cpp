// Fill out your copyright notice in the Description page of Project Settings.

#include "SKlEnemyHPWidget.h"
#include "SlateOptMacros.h"
#include "SProgressBar.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SKlEnemyHPWidget::Construct(const FArguments& InArgs)
{
	ChildSlot
	[
		SAssignNew(HPBar, SProgressBar)
	];
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SKlEnemyHPWidget::ChangeHP(float HP)
{
	HP = FMath::Clamp<float>(HP, 0.f, 1.f);
	HPBar->SetPercent(HP);

	ResultColor = FLinearColor(1.f - HP, HP, 0.f, 1.f);
	HPBar->SetFillColorAndOpacity(FSlateColor(ResultColor));
}
