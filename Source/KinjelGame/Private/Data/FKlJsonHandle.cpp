// Fill out your copyright notice in the Description page of Project Settings.

#include "FKlJsonHandle.h"
#include "Common/FKlHelper.h"
#include "Paths.h"
#include "JsonSerializer.h"

FKlJsonHandle::FKlJsonHandle()
{
	RecordDataFileName = FString("RecordData.json");
	RelativePath = FString("Res/ConfigData/");
}

void FKlJsonHandle::RecordDataJsonRead(FString& Culture, float& MusicVolume, float& SoundVolume, TArray<FString>& RecordDataList)
{
	FString JsonValue;
	LoadStringFromFile(RecordDataFileName, RelativePath, JsonValue);

	TArray<TSharedPtr<FJsonValue>> JsonParsed;
	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonValue);
	if (FJsonSerializer::Deserialize(JsonReader, JsonParsed)) {
		// Get data
		Culture = JsonParsed[0]->AsObject()->GetStringField(FString("Culture"));
		MusicVolume = JsonParsed[0]->AsObject()->GetNumberField(FString("MusicVolume"));
		SoundVolume = JsonParsed[0]->AsObject()->GetNumberField(FString("SoundVolume"));
	}
	else {
		FKlHelper::Debug("DeSerialize Failed");
	}
}

bool FKlJsonHandle::LoadStringFromFile(const FString& FileName, const FString& RelaPath, FString& ResultString)
{
	if (!FileName.IsEmpty())
	{
		// Get absolute path
		FString AbsPath = FPaths::ProjectContentDir() + RelaPath + FileName;
		if (FPaths::FileExists(AbsPath))
		{
			if (FFileHelper::LoadFileToString(ResultString, *AbsPath))
			{
				return true;
			}
			else
			{
				FKlHelper::Debug(FString("File not loaded") + AbsPath);
			}
		}
		else {
			FKlHelper::Debug(FString("File not exist") + AbsPath);
		}
	}

	return false;
}

