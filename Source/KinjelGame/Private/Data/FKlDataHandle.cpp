// Fill out your copyright notice in the Description page of Project Settings.

#include "FKlDataHandle.h"
#include "Internationalization.h"

TSharedPtr<FKlDataHandle> FKlDataHandle::DataInstance = nullptr;

void FKlDataHandle::ResetMenuVolume(float MusicVol, float SoundVol)
{
	if (MusicVol > 0)
	{
		MusicVolume = MusicVol;
	}
	if (SoundVol > 0)
	{
		SoundVolume = SoundVol;
	}
}

void FKlDataHandle::Initialize() 
{
	if (!DataInstance.IsValid())
	{
		DataInstance = Create();
	}
}

TSharedPtr<FKlDataHandle> FKlDataHandle::Get() 
{
	Initialize();

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

FKlDataHandle::FKlDataHandle() 
{
	CurrentCulture = ECultureTeam::ZH;

	MusicVolume = 0.3f;
	SoundVolume = 0.5f;
}

TSharedRef<FKlDataHandle> FKlDataHandle::Create() 
{
	TSharedRef<FKlDataHandle> DataRef = MakeShareable(new FKlDataHandle());

	return DataRef;
}
