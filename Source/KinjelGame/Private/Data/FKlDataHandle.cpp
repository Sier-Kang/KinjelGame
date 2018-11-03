// Fill out your copyright notice in the Description page of Project Settings.

#include "FKlDataHandle.h"
#include "Internationalization.h"
#include "Data/FKlSingleton.h"
#include "Data/FKlJsonHandle.h"
#include "Common/FKlHelper.h"
#include "UI/Style/KlStyle.h"
#include "UI/Style/KlMenuWidgetStyle.h"
#include "UI/Style/KlGameWidgetStyle.h"
#include "Sound/SoundCue.h"

TSharedPtr<FKlDataHandle> FKlDataHandle::DataInstance = nullptr;

void FKlDataHandle::ResetMenuVolume(float MusicVol, float SoundVol)
{
	if (MusicVol > 0)
	{
		MusicVolume = MusicVol;

		// Loop for set menu background music
		for (TArray<USoundCue*>::TIterator It(MenuAudioResource.Find(FString("Music"))->CreateIterator());
			It; It++ )
		{
			(*It)->VolumeMultiplier = MusicVolume;
		}
	}
	if (SoundVol > 0)
	{
		SoundVolume = SoundVol;

		// Loop for set menu background sound
		for (TArray<USoundCue*>::TIterator It(MenuAudioResource.Find(FString("Sound"))->CreateIterator());
			It; It++ )
		{
			(*It)->VolumeMultiplier = SoundVolume;
		}
	}

	// Update record data
	FKlSingleton<FKlJsonHandle>::Get()->UpdateRecordData(
		GetEnumValueAsString(FString("ECultureTeam"), CurrentCulture),
		MusicVolume, 
		SoundVolume, 
		&RecordDataList);
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

	// Output data
	FKlHelper::Debug(Culture + FString("--") + FString::SanitizeFloat(MusicVolume) +
		FString("--") + FString::SanitizeFloat(SoundVolume), 20.f);
	for (TArray<FString>::TIterator It(RecordDataList); It; It++)
	{
		FKlHelper::Debug(*It, 20.f);
	}
}

void FKlDataHandle::InitializeMenuAudio()
{
	// Get Style of the editor
	MenuStyle = &KlStyle::Get().GetWidgetStyle<FKlMenuStyle>("BPKlMenuStyle");

	// Add resource file
	TArray<USoundCue*> MusicList;
	MusicList.Add(
		Cast<USoundCue>(MenuStyle->MenuBackgroundMusic.GetResourceObject())
	);

	TArray<USoundCue*> SoundList;
	SoundList.Add(
		Cast<USoundCue>(MenuStyle->StartGameSound.GetResourceObject())
	);
	SoundList.Add(
		Cast<USoundCue>(MenuStyle->EndGameSound.GetResourceObject())
	);
	SoundList.Add(
		Cast<USoundCue>(MenuStyle->MenuItemChangedSound.GetResourceObject())
	);

	// Add resource to map
	MenuAudioResource.Add(FString("Music"), MusicList);
	MenuAudioResource.Add(FString("Sound"), SoundList);

	// Reset Audio
	ResetMenuVolume(MusicVolume, SoundVolume);
}

void FKlDataHandle::InitObjectAttr()
{
	FKlSingleton<FKlJsonHandle>::Get()->ObjectAttributeJsonRead(ObjectAttrMap);
	FKlHelper::Debug(ObjectAttrMap[0]->TexPath, 30.f);

	//获取GameStyle
	GameStyle = &KlStyle::Get().GetWidgetStyle<FKlGameStyle>("BPKlGameStyle");

	//填充笔刷数组
	ObjectBrushList.Add(&GameStyle->EmptyBrush);
	ObjectBrushList.Add(&GameStyle->ObjectBrush_1);
	ObjectBrushList.Add(&GameStyle->ObjectBrush_2);
	ObjectBrushList.Add(&GameStyle->ObjectBrush_3);
	ObjectBrushList.Add(&GameStyle->ObjectBrush_4);
	ObjectBrushList.Add(&GameStyle->ObjectBrush_5);
	ObjectBrushList.Add(&GameStyle->ObjectBrush_6);
	ObjectBrushList.Add(&GameStyle->ObjectBrush_7);
}

void FKlDataHandle::InitializeGameData()
{
	// Initialize object attribute
	InitObjectAttr();

	// Initialize game audio data
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

	// Update record data
	//FKlSingleton<FKlJsonHandle>::Get()->UpdateRecordData(
	//	GetEnumValueAsString(FString("ECultureTeam"), CurrentCulture),
	//	MusicVolume, 
	//	SoundVolume, 
	//	&RecordDataList);
}

FKlDataHandle::FKlDataHandle() 
{
	// Initialize record data
	InitRecordData();

	// Initialize sound audio
	InitializeMenuAudio();

	RecordName = FString("");
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