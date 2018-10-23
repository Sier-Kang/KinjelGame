// Fill out your copyright notice in the Description page of Project Settings.

#include "KlMenuWidgetStyle.h"


FKlMenuStyle::FKlMenuStyle()
{
}

FKlMenuStyle::~FKlMenuStyle()
{
}

const FName FKlMenuStyle::TypeName(TEXT("FKlMenuStyle"));

const FKlMenuStyle& FKlMenuStyle::GetDefault()
{
	static FKlMenuStyle Default;
	return Default;
}

void FKlMenuStyle::GetResources(TArray<const FSlateBrush*>& OutBrushes) const
{
	// Add any brush resources here so that Slate can correctly atlas and reference them
}

