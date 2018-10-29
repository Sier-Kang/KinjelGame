// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FKlTypes.h"

/**
 * FKlDataHandle Singleton
 */
class FKlDataHandle
{
public:
	/** Culture that game use */
	ECultureTeam CurrentCulture;

	/** Music percent volume */
	float MusicVolume;

	/** Sound percent volume */
	float SoundVolume;

	/** Record name in new game menu. */
	FString RecordName;

	/** Record Data */
	TArray<FString> RecordDataList;

	/**
	* Change current music and sound
	* @param MusicVol SoundVol
	* @return void
	*/
	void ResetMenuVolume(float MusicVol, float SoundVol);

	/**
	* Initialize record data
	* @param
	* @return 
	*/
	void InitRecordData();

public:
	static void Initialize();

	static TSharedPtr<FKlDataHandle> Get();

	/**
	* Change current Localization culture to specified.
	* @param Culture to change to 
	* @return 
	*/
	void ChangeLocalizationCulture(ECultureTeam Culture);

private:
	FKlDataHandle();

	/** Create the Singleton */
	static TSharedRef<FKlDataHandle> Create();

	/** Get Type String according to Emum Value */
	template<typename TEnum>
	FString GetEnumValueAsString(const FString& Name, TEnum Value);

	template<typename TEnum>
	TEnum GetEnumValueFromString(const FString& Name, FString Value);

private:
	static TSharedPtr<FKlDataHandle> DataInstance;
};


