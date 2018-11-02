// Fill out your copyright notice in the Description page of Project Settings.

#include "KlGameWidgetStyle.h"


FKlGameStyle::FKlGameStyle()
{
}

FKlGameStyle::~FKlGameStyle()
{
}

const FName FKlGameStyle::TypeName(TEXT("FKlGameStyle"));

const FKlGameStyle& FKlGameStyle::GetDefault()
{
	static FKlGameStyle Default;
	return Default;
}

void FKlGameStyle::GetResources(TArray<const FSlateBrush*>& OutBrushes) const
{
	// Add any brush resources here so that Slate can correctly atlas and reference them
}

