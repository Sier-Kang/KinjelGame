// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FKlTypes.h"

class USoundCue;

/**
 * FKlDataHandle Singleton
 */
class FKlDataHandle
{
public:
	static void Initialize();

	static TSharedPtr<FKlDataHandle> Get();

	/**
	* Change current Localization culture to specified.
	* @param Culture to change to 
	* @return 
	*/
	void ChangeLocalizationCulture(ECultureTeam Culture);

	/**
	* Change current music and sound
	* @param MusicVol SoundVol
	* @return void
	*/
	void ResetMenuVolume(float MusicVol, float SoundVol);

	/**
	* Change current music and sound
	* @param MusicVol SoundVol
	* @return void
	*/
	void ResetGameVolume(float MusicVol, float SoundVol);

	/**
	* Initialize record data
	* @param
	* @return
	*/
	void InitRecordData();

	/**
	* Initialize music&sound audio
	*/
	void InitializeMenuAudio();

	/**
	* Initialize Object attribute
	*/
	void InitObjectAttr();

	/**
	* Initialize Resource attribute
	*/
	void InitResourceAttr();

	/**
	* Game data initialize
	*/
	void InitializeGameData();

	/**
	* Initialize CompoundTable 
	*/
	void InitCompoundTableMap();

	/**
	* Initialize game audio
	*/
	void InitializeGameAudio();

	/** Add new record */
	void AddNewRecord();

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

	/** Object attribute information */
	TMap<int, TSharedPtr<ObjectAttribute>> ObjectAttrMap;

	/** Resource attribute information */
	TMap<int, TSharedPtr<ResourceAttribute>> ResourceAttrMap;

	/** Object texture resources */
	TArray<const FSlateBrush*> ObjectBrushList;

	/** Compound Table Map */
	TArray<TSharedPtr<CompoundTable>> CompoundTableMap;

private:
	FKlDataHandle();

	/** Create the Singleton */
	static TSharedRef<FKlDataHandle> Create();

	/** Get Type String according to Enum Value */
	template<typename TEnum>
	FString GetEnumValueAsString(const FString& Name, TEnum Value);

	template<typename TEnum>
	TEnum GetEnumValueFromString(const FString& Name, FString Value);

private:
	/** Get the style of menu */
	const struct FKlMenuStyle* MenuStyle;

	/** Get the style of Game */
	const struct FKlGameStyle* GameStyle;

	// Global instance - singleton
	static TSharedPtr<FKlDataHandle> DataInstance;

	// Audio control
	TMap<FString, TArray<USoundCue*>> MenuAudioResource;

	/** Music components */
	class USoundMix* KlSoundMix;

	class USoundClass* KlMusicClass;

	USoundClass* KlSoundClass;

	class FAudioDevice* AudioDevice;
};


