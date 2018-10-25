// Fill out your copyright notice in the Description page of Project Settings.

#include "FKlDataHandle.h"
#include "Internationalization.h"

TSharedPtr<FKlDataHandle> FKlDataHandle::DataInstance = nullptr;

void FKlDataHandle::Initialize() 
{
	if (!DataInstance.IsValid())
	{
		DataInstance = Create();
	}
}

TSharedPtr<FKlDataHandle> FKlDataHandle::Get() 
{
	return DataInstance;
}

void FKlDataHandle::ChangeLocalizationCulture(ECultureTeam Culture) 
{
	switch (Culture)
	{
	case ECultureTeam::EN:
		FInternationalization::Get().SetCurrentCulture(TEXT("en"));

		break;
	case ECultureTeam::ZH:
		FInternationalization::Get().SetCurrentCulture(TEXT("zh"));

		break;
	default:
		break;
	}

	CurrentCulture = Culture;
}

TSharedRef<FKlDataHandle> FKlDataHandle::Create() 
{
	TSharedRef<FKlDataHandle> DataRef = MakeShareable(new FKlDataHandle());

	return DataRef;
}
