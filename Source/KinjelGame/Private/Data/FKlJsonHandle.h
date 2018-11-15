// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/FKlTypes.h"
#include "Json.h"

/**
 * 
 */
class FKlJsonHandle
{
public:
	/** Constructor */
	FKlJsonHandle();

	/**
	* Parse record data to game info.
	*
	* @param Culture Current culture.
	* @param MusicVolume Music volume.
	* @param SoundVolume Sound volume.
	* @param RecordDataList Record data list.
	* @return
	*/
	void RecordDataJsonRead(FString& Culture, float& MusicVolume,
		float& SoundVolume, TArray<FString>& RecordDataList);

	/**
	* Update record data to game info.
	*
	* @param Culture Current culture.
	* @param MusicVolume Music volume.
	* @param SoundVolume Sound volume.
	* @param RecordDataList Record data list.
	* @return
	*/
	void UpdateRecordData(FString Culture, float MusicVolume, float SoundVolume, TArray<FString>*
		RecordDataList);

	/**
	* Parse Object attribute information
	*/
	void ObjectAttributeJsonRead(TMap<int, TSharedPtr<ObjectAttribute>>& ObjectAttrMap);

	/**
	* Parse Resource attribute information
	*/
	void ResourceAttrJsonRead(TMap<int, TSharedPtr<ResourceAttribute>>& ResourceAttrMap);

	/**
	* Parse compound table 
	*/
	void CompoundTableJsonRead(TArray<TSharedPtr<CompoundTable>>& CompoundTableMap);
private:
	/**
	* Read json file to string.
	* 
	*@param FileName Name of the file.
	*@param RelaPath Relative path of the file.
	*@param ResultString Readed string from file.
	*@return Success or not
	*/
	bool LoadStringFromFile(const FString& FileName, const FString& RelaPath, FString& ResultString);

	/**
	* Save data to json file.
	*
	*@param JsonStr String that save to json file.
	*@param RelaPath Relative path of the file.
	*@param FileName File name of the json file.
	*@return Success or not
	*/
	bool WriteFileWithJsonData(const FString& JsonStr, const FString& RelaPath, const FString& FileName);

	/**
	* Convert JsonObject to Json format string.
	*
	*@param JsonObj Json Object that to convert.
	*@param JsonStr Converted string that in Json format
	*@return Success or not
	*/
	bool GetFStringInJsonData(const TSharedPtr<FJsonObject>& JsonObj, FString& JsonStr);

	/**
	* Convert Object Type info from string to enum
	*/
	EObjectType::Type StringToObjectType(const FString ArgStr);

	/**
	* Convert to resource type from string
	*/
	EResourceType::Type StringToResourceType(const FString ArgStr);

private:
	// Document name
	FString RecordDataFileName;

	// Object attribute file name
	FString ObjectAttrFileName;

	// Resource attribute file name
	FString ResourceAttrFileName;

	// Compound Table file name
	FString CompoundTableFileName;

	// Relative path
	FString RelativePath;
};
