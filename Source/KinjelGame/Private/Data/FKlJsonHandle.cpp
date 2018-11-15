// Fill out your copyright notice in the Description page of Project Settings.

#include "FKlJsonHandle.h"
#include "Common/FKlHelper.h"
#include "Paths.h"
#include "JsonSerializer.h"
#include "JsonSerializerMacros.h"

FKlJsonHandle::FKlJsonHandle()
{
	RecordDataFileName = FString("RecordData.json");
	ObjectAttrFileName = FString("ObjectAttribute.json");
	ResourceAttrFileName = FString("ResourceAttribute.json");
	CompoundTableFileName = FString("CompoundTable.json");

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

void FKlJsonHandle::ObjectAttributeJsonRead(TMap<int, TSharedPtr<ObjectAttribute>>& ObjectAttrMap)
{
	FString JsonValue;
	LoadStringFromFile(ObjectAttrFileName, RelativePath, JsonValue);

	TArray<TSharedPtr<FJsonValue>> JsonParsed;
	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonValue);

	if (FJsonSerializer::Deserialize(JsonReader, JsonParsed)){
		for (int i = 0; i < JsonParsed.Num(); i++) {
			TArray<TSharedPtr<FJsonValue>> ObjectAttr =
				JsonParsed[i]->AsObject()->GetArrayField(FString::FromInt(i));
			// Parse object attributes.
			FText EN = FText::FromString(ObjectAttr[0]->AsObject()->GetStringField("EN"));
			FText ZH = FText::FromString(ObjectAttr[1]->AsObject()->GetStringField("ZH"));
			FString ObjectTypeStr = ObjectAttr[2]->AsObject()->GetStringField("ObjectType");
			int PlantAttack = ObjectAttr[3]->AsObject()->GetIntegerField("PlantAttack");
			int MetalAttcck = ObjectAttr[4]->AsObject()->GetIntegerField("MetalAttcck");
			int AnimalAttack = ObjectAttr[5]->AsObject()->GetIntegerField("AnimalAttack");
			int AffectRange = ObjectAttr[6]->AsObject()->GetIntegerField("AffectRange");
			FString TexPath = ObjectAttr[7]->AsObject()->GetStringField("TexPath");

			EObjectType::Type ObjectType = StringToObjectType(ObjectTypeStr);
			TSharedPtr<ObjectAttribute> ObjectAttrPtr = MakeShareable(new ObjectAttribute(EN, ZH, ObjectType, PlantAttack, MetalAttcck, AnimalAttack, AffectRange, TexPath));

			ObjectAttrMap.Add(i, ObjectAttrPtr);
		}
	}
	else {
		FKlHelper::Debug("DeSerialize Failed");
	}
}

void FKlJsonHandle::ResourceAttrJsonRead(TMap<int, TSharedPtr<ResourceAttribute>>& ResourceAttrMap)
{
	FString JsonValue;
	LoadStringFromFile(ResourceAttrFileName, RelativePath, JsonValue);

	TArray<TSharedPtr<FJsonValue>> JsonParsed;
	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonValue);

	if (FJsonSerializer::Deserialize(JsonReader, JsonParsed))
	{
		for (int i = 0; i < JsonParsed.Num(); ++i) {
			//Resource has no index 0, begin with 1.
			TArray<TSharedPtr<FJsonValue>> ResourceAttr = JsonParsed[i]->AsObject()->GetArrayField(FString::FromInt(i + 1));
			FText EN = FText::FromString(ResourceAttr[0]->AsObject()->GetStringField("EN"));
			FText ZH = FText::FromString(ResourceAttr[1]->AsObject()->GetStringField("ZH"));
			EResourceType::Type ResourceType = StringToResourceType(ResourceAttr[2]->AsObject()->GetStringField("ResourceType"));
			int HP = ResourceAttr[3]->AsObject()->GetIntegerField("HP");

			TArray<TArray<int>> FlobObjectInfoArray;

			TArray<TSharedPtr<FJsonValue>> FlobObjectInfo = ResourceAttr[4]->AsObject()->GetArrayField(FString("FlobObjectInfo"));

			for (int j = 0; j < FlobObjectInfo.Num(); ++j) {

				FString FlobObjectInfoItem = FlobObjectInfo[j]->AsObject()->GetStringField(FString::FromInt(j));
				FString ObjectIndexStr;
				FString RangeStr;
				FString RangeMinStr;
				FString RangeMaxStr;
				FlobObjectInfoItem.Split(FString("_"), &ObjectIndexStr, &RangeStr);
				RangeStr.Split(FString(","), &RangeMinStr, &RangeMaxStr);

				TArray<int> FlobObjectInfoList;

				FlobObjectInfoList.Add(FCString::Atoi(*ObjectIndexStr));
				FlobObjectInfoList.Add(FCString::Atoi(*RangeMinStr));
				FlobObjectInfoList.Add(FCString::Atoi(*RangeMaxStr));

				FlobObjectInfoArray.Add(FlobObjectInfoList);
			}

			TSharedPtr<ResourceAttribute> ResourceAttrPtr = MakeShareable(new ResourceAttribute(EN, ZH, ResourceType, HP, &FlobObjectInfoArray));

			ResourceAttrMap.Add(i + 1, ResourceAttrPtr);
			
			// Debug Info
			// FKlHelper::Debug(ResourceAttrPtr->ToString(), 10.f);
		}
	}
	else
	{
		FKlHelper::Debug(FString("Deserialize Failed"), 10.f);
	}
}

void FKlJsonHandle::CompoundTableJsonRead(TArray<TSharedPtr<CompoundTable>>& CompoundTableMap)
{
	FString JsonValue;
	LoadStringFromFile(CompoundTableFileName, RelativePath, JsonValue);

	TArray<TSharedPtr<FJsonValue>> JsonParsed;
	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonValue);

	if (FJsonSerializer::Deserialize(JsonReader, JsonParsed))
	{

		for (int i = 0; i < JsonParsed.Num(); ++i) {
			TArray<TSharedPtr<FJsonValue>> ObjectAttr = JsonParsed[i]->AsObject()->GetArrayField(FString::FromInt(i));

			TArray<int> CompoundTableArr;

			for (int j = 0; j < 10; ++j) {
				CompoundTableArr.Add(ObjectAttr[j]->AsObject()->GetIntegerField(FString::FromInt(j)));
			}

			TSharedPtr<CompoundTable> NewTable = MakeShareable(new CompoundTable(&CompoundTableArr));

			CompoundTableMap.Add(NewTable);

		}

	}
	else {
		FKlHelper::Debug(FString("Deserialize Failed"));
	}
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

EObjectType::Type FKlJsonHandle::StringToObjectType(const FString ArgStr)
{
	if (ArgStr.Equals(FString("Normal"))) return EObjectType::Normal;
	if (ArgStr.Equals(FString("Food"))) return EObjectType::Food;
	if (ArgStr.Equals(FString("Tool"))) return EObjectType::Tool;
	if (ArgStr.Equals(FString("Weapon"))) return EObjectType::Weapon;

	return EObjectType::Normal;
}

EResourceType::Type FKlJsonHandle::StringToResourceType(const FString ArgStr)
{
	if (ArgStr.Equals(FString("Plant"))) 
		return EResourceType::Plant;

	if (ArgStr.Equals(FString("Metal"))) 
		return EResourceType::Metal;

	if (ArgStr.Equals(FString("Animal")))
		return EResourceType::Animal;

	return EResourceType::Plant;
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

