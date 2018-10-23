// Fill out your copyright notice in the Description page of Project Settings.

#include "KlStyle.h"
#include "SlateGameResources.h"

TSharedPtr<FSlateStyleSet> KlStyle::KlStyleInstance = nullptr;

void KlStyle::Initialize() 
{
	if (!KlStyleInstance.IsValid())
	{
		KlStyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*KlStyleInstance);
	}
}

FName KlStyle::GetStyleSetName() 
{
	static FName SlateSetName(TEXT("KlStyle"));

	return SlateSetName;
}

void KlStyle::ShutDown() 
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*KlStyleInstance);
	ensure(KlStyleInstance.IsUnique());
	KlStyleInstance.Reset();
}

const ISlateStyle& KlStyle::Get() 
{
	return *KlStyleInstance;
}

TSharedRef<class FSlateStyleSet> KlStyle::Create() 
{
	TSharedRef<FSlateStyleSet> StyleRef = FSlateGameResources::New(
		KlStyle::GetStyleSetName(),
		"/Game/UI/Style",
		"/Game/UI/Style"
	);

	return StyleRef;
}
