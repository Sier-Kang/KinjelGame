// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SlateBasics.h"
#include "Widgets/SCompoundWidget.h"
#include "Data/FKlTypes.h"

// Save record delegate 
DECLARE_DELEGATE(FSaveGameDelegate)


/**
 * 
 */
class SKlGameMenuWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SKlGameMenuWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	/** Game lose */
	void GameLose();

	/** Reset menu */
	void ResetMenu();

public:
	// Bind to Game mode's SaveGame()
	FSaveGameDelegate SaveGameDele;

private:
	void InitializeWidget();

	FReply OptionEvent();

	FReply SaveGameEvent();

	FReply QuitGameEvent();

	FReply GoBackEvent();

	/** Change culture */
	void ChangeCulture(ECultureTeam Culture);

	/** Change sound */
	void ChangeVolume(const float MusicVolume, const float SoundVolume);

private:
	/** Get Game Style */
	const struct FKlGameStyle *GameStyle;

	TSharedPtr<class SBox> RootBox;

	TSharedPtr<class SVerticalBox> VertBox;

	TSharedPtr<SButton> SaveGameButton;

	TSharedPtr<class STextBlock> SaveGameText;

	TSharedPtr<class SButton> QuitGameButton;


	TArray<TSharedPtr<SCompoundWidget>> MenuItemList;

	TArray<TSharedPtr<SCompoundWidget>> OptionItemList;
};
