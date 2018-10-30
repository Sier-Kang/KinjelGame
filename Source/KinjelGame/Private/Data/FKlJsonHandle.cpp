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
	//FKlHelper::Debug(FString("json string") + JsonValue, 100.f);

	TArray<TSharedPtr<FJsonValue>> JsonParsed;
	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonValue);
	if (FJsonSerializer::Deserialize(JsonReader, JsonParsed)) {
		// Get Settings
		Culture = JsonParsed[0]->AsObject()->GetStringField(FString("Culture"));
		MusicVolume = JsonParsed[1]->AsObject()->GetNumberField(FString("MusicVolume"));
		SoundVolume = JsonParsed[2]->AsObject()->GetNumberField(FString("SoundVolume"));

		// Get Record data
		TArray<TSharedPtr<FJsonValue>> RecordDataArray = JsonParsed[3]->AsObject()->GetArrayField(FString("RecordData"));
		for (int i = 0; i < RecordDataArray.Num(); i++) {
			FString RecordDataName = RecordDataArray[i]->AsObject()->GetStringField(FString::FromInt(i));
			RecordDataList.Add(RecordDataName);
			//FKlHelper::Debug(FString("test: ") + RecordDataName, 200.f);
		}
	}
	else {
		FKlHelper::Debug("DeSerialize Failed");
	}
}

void FKlJsonHandle::UpdateRecordData(FString Culture, float MusicVolume, float SoundVolume, TArray<FString>* RecordDataList)
{
	TSharedPtr<FJsonObject> JsonObj = MakeShareable(new FJsonObject);

	TArray<TSharedPtr<FJsonValue>> BaseDataArray;

	// make record json values.
	TSharedPtr<FJsonObject> CultureObj = MakeShareable(new FJsonObject);
	CultureObj->SetStringField("Culture", Culture);
	TSharedPtr<FJsonValueObject> CultureValue = MakeShareable(new FJsonValueObject(CultureObj));

	TSharedPtr<FJsonObject> MusicVolumeObj = MakeShareable(new FJsonObject);
	MusicVolumeObj->SetNumberField("MusicVolume", MusicVolume);
	TSharedPtr<FJsonValueObject> MusicVolumeValue = MakeShareable(new FJsonValueObject(MusicVolumeObj));

	TSharedPtr<FJsonObject> SoundVolumeObj = MakeShareable(new FJsonObject);
	SoundVolumeObj->SetNumberField("SoundVolume", SoundVolume);
	TSharedPtr<FJsonValueObject> SoundVolumeValue = MakeShareable(new FJsonValueObject(SoundVolumeObj));

	TArray<TSharedPtr<FJsonValue>> RecordDataArray;
	for (int i = 0; i < RecordDataList->Num(); i++) {
		TSharedPtr<FJsonObject> RecordItem = MakeShareable(new FJsonObject);
		RecordItem->SetStringField(FString::FromInt(i), (*RecordDataList)[i]);
		TSharedPtr<FJsonValueObject> RecordItemValue = MakeShareable(new FJsonValueObject(RecordItem));

		RecordDataArray.Add(RecordItemValue);
	}

	TSharedPtr<FJsonObject> RecordDataObject = MakeShareable(new FJsonObject);
	RecordDataObject->SetArrayField("RecordData", RecordDataArray);

	TSharedPtr<FJsonValueObject> RecordDataValue = MakeShareable(new FJsonValueObject(RecordDataObject));

	BaseDataArray.Add(CultureValue);
	BaseDataArray.Add(MusicVolumeValue);
	BaseDataArray.Add(SoundVolumeValue);
	BaseDataArray.Add(RecordDataValue);

	JsonObj->SetArrayField(FString("T"), BaseDataArray);

	FString JsonStr;
	GetFStringInJsonData(JsonObj, JsonStr);

	FKlHelper::Debug(FString("Origin String: ") + JsonStr, 10.0f);

	// Remove unnecessary words in json string.
	JsonStr.RemoveAt(0, 8);
	JsonStr.RemoveFromEnd(FString("}"));

	FKlHelper::Debug(FString("Final string: ") + JsonStr, 10.0f);

	// Write to file
	WriteFileWithJsonData(JsonStr, RelativePath, RecordDataFileName);
}

bool FKlJsonHandle::WriteFileWithJsonData(const FString& JsonStr, const FString& RelaPath, const FString& FileName)
{
	if (!JsonStr.IsEmpty())
	{
		if (!FileName.IsEmpty())
		{
			FString AbsPath = FPaths::ProjectContentDir() + RelaPath + FileName;
			// Save
			if (FFileHelper::SaveStringToFile(JsonStr, *AbsPath)) {
				return true;
			} else {
				FKlHelper::Debug(FString("Save") + AbsPath + FString("-->Failed."), 20.f);
			}
		}
		else {
			FKlHelper::Debug(FString("File name is empty!"), 20.f);
		}
	} else {
		FKlHelper::Debug(FString("Json string is empty!"), 20.f);
	}

	return false;
}

bool FKlJsonHandle::GetFStringInJsonData(const TSharedPtr<FJsonObject>& JsonObj, FString& JsonStr)
{
	if (JsonObj.IsValid() && JsonObj->Values.Num() > 0)
	{
		TSharedRef<TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<TCHAR>::Create(&JsonStr);
		FJsonSerializer::Serialize(JsonObj.ToSharedRef(), JsonWriter);

		return true;
	}

	return false;
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

