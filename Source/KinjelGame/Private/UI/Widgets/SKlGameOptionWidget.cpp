// Fill out your copyright notice in the Description page of Project Settings.

#include "SKlGameOptionWidget.h"
#include "SlateOptMacros.h"
#include "UI/Style/KlStyle.h"
#include "UI/Style/KlMenuWidgetStyle.h"
#include "Common/FKlHelper.h"
#include "SBox.h"
#include "SImage.h"
#include "SBorder.h"
#include "SOverlay.h"
#include "STextBlock.h"
#include "SBoxPanel.h"
#include "SSlider.h"
#include "Data/FKlDataHandle.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SKlGameOptionWidget::Construct(const FArguments& InArgs)
{
	// Get Style of the editor
	MenuStyle = &KlStyle::Get().GetWidgetStyle<FKlMenuStyle>("BPKlMenuStyle");

	ChildSlot
	[
		SNew(SBox)
		.WidthOverride(500.f)
		.HeightOverride(300.f)
		[
			SNew(SOverlay)
			// Menu Background
			+SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SImage)
				.Image(&MenuStyle->GameOptionBGBrush)
			]
			// Menu Content
			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(FMargin(50.f))
			[
				SNew(SVerticalBox)
				// Culture Setting
				+SVerticalBox::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.FillHeight(1.f)
				[
					SNew(SHorizontalBox)
					// Chinese Culture
					+ SHorizontalBox::Slot()
					.HAlign(HAlign_Center)
					.VAlign(VAlign_Center)
					.FillWidth(1.f)
					[
						SAssignNew(ZhCheckBox, SCheckBox)
						.OnCheckStateChanged(this, &SKlGameOptionWidget::ZhCheckBoxStateChanged)
						[
							SNew(STextBlock)
							.Font(MenuStyle->Font_40)
							.ColorAndOpacity(MenuStyle->FontColor_Black)
							.Text(NSLOCTEXT("KlMenu", "Chinese", "Chinese"))
						]
					]
					// English Culture
					+ SHorizontalBox::Slot()
					.HAlign(HAlign_Center)
					.VAlign(VAlign_Center)
					.FillWidth(1.f)
					[
						SAssignNew(EnCheckBox, SCheckBox)
						.OnCheckStateChanged(this, &SKlGameOptionWidget::EnCheckBoxStateChanged)
						[
							SNew(STextBlock)
							.Font(MenuStyle->Font_40)
							.ColorAndOpacity(MenuStyle->FontColor_White)
							.Text(NSLOCTEXT("KlMenu", "English", "English"))
						]
					]
				]
				// Music Setting
				+ SVerticalBox::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.FillHeight(1.f)
				[
					SNew(SOverlay)
					// Music Text
					+ SOverlay::Slot()
					.HAlign(HAlign_Left)
					.VAlign(VAlign_Center)
					[
						SNew(STextBlock)
						.Font(MenuStyle->Font_40)
						.ColorAndOpacity(MenuStyle->FontColor_Black)
						.Text(NSLOCTEXT("KlMenu", "Music", "Music"))
					]
					// Music Slider
					+ SOverlay::Slot()
					.HAlign(HAlign_Center)
					.VAlign(VAlign_Center)
					[
						SNew(SBox)
						.WidthOverride(240.f)
						[
							SNew(SOverlay)
							// Slider background
							+ SOverlay::Slot()
							.HAlign(HAlign_Fill)
							.VAlign(VAlign_Center)
							.Padding(FMargin(30.f, 0.f))
							[
								SNew(SImage)
								.Image(&MenuStyle->SliderBarBrush)
							]
							// Music Slider
							+ SOverlay::Slot()
							.HAlign(HAlign_Fill)
							.VAlign(VAlign_Center)
							[
								SAssignNew(MusicSlider, SSlider)
								.Style(&MenuStyle->SliderStyle)
								.OnValueChanged(this, &SKlGameOptionWidget::MusicSliderChanged)
							]
						]
					]
					// Percent text of music 
					+ SOverlay::Slot()
					.HAlign(HAlign_Right)
					.VAlign(VAlign_Center)
					[
						SAssignNew(MusicPercentTextBlock, STextBlock)
						.Font(MenuStyle->Font_40)
						.ColorAndOpacity(MenuStyle->FontColor_White)
					]
				]
				// Sound Setting
				+ SVerticalBox::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.FillHeight(1.f)
				[
					SNew(SOverlay)
					// Sound Text
					+ SOverlay::Slot()
					.HAlign(HAlign_Left)
					.VAlign(VAlign_Center)
					[
						SNew(STextBlock)
						.Font(MenuStyle->Font_40)
						.ColorAndOpacity(MenuStyle->FontColor_Black)
						.Text(NSLOCTEXT("KlMenu", "Sound", "Sound"))
					]
					// Sound Slider
					+ SOverlay::Slot()
					.HAlign(HAlign_Center)
					.VAlign(VAlign_Center)
					[
						SNew(SBox)
						.WidthOverride(240.f)
						[
							SNew(SOverlay)
							// Slider background
							+ SOverlay::Slot()
							.HAlign(HAlign_Fill)
							.VAlign(VAlign_Center)
							.Padding(FMargin(30.f, 0.f))
							[
								SNew(SImage)
								.Image(&MenuStyle->SliderBarBrush)
							]
							// Music Slider
							+ SOverlay::Slot()
							.HAlign(HAlign_Fill)
							.VAlign(VAlign_Center)
							[
								SAssignNew(SoundSlider, SSlider)
								.Style(&MenuStyle->SliderStyle)
								.OnValueChanged(this, &SKlGameOptionWidget::SoundSliderChanged)
							]
						]
					]
					// Percent text of sound 
					+ SOverlay::Slot()
					.HAlign(HAlign_Right)
					.VAlign(VAlign_Center)
					[
						SAssignNew(SoundPercentTextBlock, STextBlock)
						.Font(MenuStyle->Font_40)
						.ColorAndOpacity(MenuStyle->FontColor_White)
					]
				]
			]
		]
	];

	// Initialize the Culture CheckBox style.
	StyleInitialize();
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SKlGameOptionWidget::ZhCheckBoxStateChanged(ECheckBoxState NewState) 
{
	FKlHelper::Debug(FString("ZhCheckBox state changed."), 10.f);
	// Set Style
	ZhCheckBox->SetIsChecked(ECheckBoxState::Checked);
	EnCheckBox->SetIsChecked(ECheckBoxState::Unchecked);

	// Set current culture
	FKlDataHandle::Get()->ChangeLocalizationCulture(ECultureTeam::ZH);
}

void SKlGameOptionWidget::EnCheckBoxStateChanged(ECheckBoxState NewState)
{
	FKlHelper::Debug(FString("EnCheckBox state changed."), 10.f);

	// Set Style
	EnCheckBox->SetIsChecked(ECheckBoxState::Checked);
	ZhCheckBox->SetIsChecked(ECheckBoxState::Unchecked);

	// Set current culture
	FKlDataHandle::Get()->ChangeLocalizationCulture(ECultureTeam::EN);
}

void SKlGameOptionWidget::MusicSliderChanged(float Value) 
{
	// Show percent of music 
	MusicPercentTextBlock->SetText(FText::FromString(FString::FromInt(FMath::RoundToInt(Value * 100)) + FString("%")));
}

void SKlGameOptionWidget::SoundSliderChanged(float Value) 
{
	// Show percent of music 
	SoundPercentTextBlock->SetText(FText::FromString(FString::FromInt(FMath::RoundToInt(Value * 100)) + FString("%")));
}

void SKlGameOptionWidget::StyleInitialize() 
{
	// Set ZhCheckBox style
	ZhCheckBox->SetUncheckedImage(&MenuStyle->UnCheckedBoxBrush);
	ZhCheckBox->SetUncheckedHoveredImage(&MenuStyle->UnCheckedBoxBrush);
	ZhCheckBox->SetUncheckedPressedImage(&MenuStyle->UnCheckedBoxBrush);
	ZhCheckBox->SetCheckedImage(&MenuStyle->CheckedBoxBrush);
	ZhCheckBox->SetCheckedHoveredImage(&MenuStyle->CheckedBoxBrush);
	ZhCheckBox->SetCheckedPressedImage(&MenuStyle->CheckedBoxBrush);

	// Set EnCheckBox style
	EnCheckBox->SetUncheckedImage(&MenuStyle->UnCheckedBoxBrush);
	EnCheckBox->SetUncheckedHoveredImage(&MenuStyle->UnCheckedBoxBrush);
	EnCheckBox->SetUncheckedPressedImage(&MenuStyle->UnCheckedBoxBrush);
	EnCheckBox->SetCheckedImage(&MenuStyle->CheckedBoxBrush);
	EnCheckBox->SetCheckedHoveredImage(&MenuStyle->CheckedBoxBrush);
	EnCheckBox->SetCheckedPressedImage(&MenuStyle->CheckedBoxBrush);

	// CheckBox State
	switch (FKlDataHandle::Get()->CurrentCulture)
	{
	case ECultureTeam::ZH:
		ZhCheckBox->SetIsChecked(ECheckBoxState::Checked);
		EnCheckBox->SetIsChecked(ECheckBoxState::Unchecked);

		break;
	case ECultureTeam::EN:
		ZhCheckBox->SetIsChecked(ECheckBoxState::Unchecked);
		EnCheckBox->SetIsChecked(ECheckBoxState::Checked);

		break;
	default:

		break;
	}

	MusicSlider->SetValue(FKlDataHandle::Get()->MusicVolume);
	SoundSlider->SetValue(FKlDataHandle::Get()->SoundVolume);

	MusicPercentTextBlock->SetText(FText::FromString(FString::FromInt(FMath::RoundToInt(FKlDataHandle::Get()->MusicVolume * 100)) + FString("%")));
	SoundPercentTextBlock->SetText(FText::FromString(FString::FromInt(FMath::RoundToInt(FKlDataHandle::Get()->SoundVolume * 100)) + FString("%")));
}
