// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/FKlTypes.h"
#include "Widgets/SCompoundWidget.h"

// Delegate of Change Culture
DECLARE_DELEGATE_OneParam(FChangeCulture, const ECultureTeam)

// Delegate of Change Volume
DECLARE_DELEGATE_TwoParams(FChangeVolume, const float, const float)

class SSlider;

/**
 * 
 */
class SKlGameOptionWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SKlGameOptionWidget)
	{}
	SLATE_EVENT(FChangeCulture, ChangeCulture)

	SLATE_EVENT(FChangeVolume, ChangeVolume)

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

private:
	/**
	* Culture changed to Chinese
	* @param State that changed
	* @return void
	*/
	void ZhCheckBoxStateChanged(ECheckBoxState NewState);

	/**
	* Culture changed to English
	* @param State that changed
	* @return void
	*/
	void EnCheckBoxStateChanged(ECheckBoxState NewState);

	/** 
	* Music changed
	* @param changed value 
	* @return void 
	*/
	void MusicSliderChanged(float Value);

	/**
	* Sound changed
	* @param changed value
	* @return void
	*/
	void SoundSliderChanged(float Value);

	/** 
	* Culture CheckBox style initialize
	* @param 
	* @return void 
	*/
	void StyleInitialize();

private:
	/** Get the style of menu */
	const struct FKlMenuStyle* MenuStyle;

	/** CheckBox of English */
	TSharedPtr<SCheckBox> EnCheckBox;

	/** CheckBox of Chinese */
	TSharedPtr<SCheckBox> ZhCheckBox;

	/** Music Slider */
	TSharedPtr<SSlider> MusicSlider;

	/** Sound Slider */
	TSharedPtr<SSlider> SoundSlider;

	/** Percent of Music text */
	TSharedPtr<STextBlock> MusicPercentTextBlock;

	/** Percent of Sound text */
	TSharedPtr<STextBlock> SoundPercentTextBlock;

	/** Delegate */
	FChangeCulture ChangeCulture;

	FChangeVolume ChangeVolume;
};
