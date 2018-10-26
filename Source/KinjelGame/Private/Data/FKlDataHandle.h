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

private:
	static TSharedPtr<FKlDataHandle> DataInstance;
};