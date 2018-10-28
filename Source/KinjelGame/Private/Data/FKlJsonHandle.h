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
	FKlJsonHandle();

	/**
	* Parse json string to game info.
	* @param
	* @return
	*/
	void RecordDataJsonRead(FString& Culture, float& MusicVolume,
		float& SoundVolume, TArray<FString>& RecordDataList);

private:
	// Read json file to string
	bool LoadStringFromFile(const FString& FileName, const FString& RelaPath, FString& ResultString);

private:
	// Document name
	FString RecordDataFileName;

	// Relative path
	FString RelativePath;
};
