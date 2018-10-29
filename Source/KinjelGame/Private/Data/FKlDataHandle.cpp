// Fill out your copyright notice in the Description page of Project Settings.

#include "FKlDataHandle.h"
#include "Internationalization.h"
#include "Data/FKlSingleton.h"
#include "Data/FKlJsonHandle.h"
#include "Common/FKlHelper.h"

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

	// Update record data
	FKlSingleton<FKlJsonHandle>::Get()->UpdateRecordData(GetEnumValueAsString(FString("ECultureTeam"), CurrentCulture),
		MusicVolume, SoundVolume, &RecordDataList);
}

void FKlDataHandle::InitRecordData()
{
	// Get Culture
	FString Culture;

	// Read record
	FKlSingleton<FKlJsonHandle>::Get()->RecordDataJsonRead(Culture, MusicVolume, SoundVolume, RecordDataList);

	// Initialize culture
	ChangeLocalizationCulture(GetEnumValueFromString<ECultureTeam>(FString("ECultureTeam"), Culture));
	//CurrentCulture = Culture;

	// Initialize volume

	// Output data
	FKlHelper::Debug(Culture + FString("--") + FString::SanitizeFloat(MusicVolume) + FString("--") + FString::SanitizeFloat(SoundVolume), 20.f);
	for (TArray<FString>::TIterator It(RecordDataList); It; It++)
	{
		FKlHelper::Debug(*It, 20.f);
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
	// Initialize record data
	InitRecordData();
}

TSharedRef<FKlDataHandle> FKlDataHandle::Create() 
{
	TSharedRef<FKlDataHandle> DataRef = MakeShareable(new FKlDataHandle());

	return DataRef;
}

template<typename TEnum>
FString FKlDataHandle::GetEnumValueAsString(const FString& Name, TEnum Value)
{
	const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, *Name, true);
	if (!EnumPtr) {
		return FString("InValid");
	}

	return EnumPtr->GetNameStringByIndex((int32)Value);
}

template<typename TEnum>
TEnum FKlDataHandle::GetEnumValueFromString(const FString& Name, FString Value)
{
	const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, *Name, true);
	if (!EnumPtr) {
		return TEnum(0);
	}

	return (TEnum)EnumPtr->GetIndexByName(FName(*FString(Value)));
}