// Fill out your copyright notice in the Description page of Project Settings.

#include "SKlGameMenuWidget.h"
#include "SlateOptMacros.h"
#include "UI/Style/KlStyle.h"
#include "UI/Style/KlGameWidgetStyle.h"
#include "SBox.h"
#include "SOverlay.h"
#include "SBoxPanel.h"
#include "SBorder.h"
#include "STextBlock.h"
#include "SMultiLineEditableText.h"
#include "SScrollBox.h"
#include "SEditableTextBox.h"
#include "SButton.h"
#include "STextBlock.h"
#include "SKlGameOptionWidget.h"
#include "KlPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Data/FKlDataHandle.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SKlGameMenuWidget::Construct(const FArguments& InArgs)
{
	//Get GameStyle
	GameStyle = &KlStyle::Get().GetWidgetStyle<FKlGameStyle>("BPKlGameStyle");

	ChildSlot
		[
			SAssignNew(RootBox, SBox)
			.WidthOverride(600.f)
			.HeightOverride(400.f)
			.Padding(FMargin(50.f))
			[
				SAssignNew(VertBox, SVerticalBox)
			]
		];

	InitializeWidget();
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SKlGameMenuWidget::GameLose()
{
	VertBox->ClearChildren();

	VertBox->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(10.f)
		.FillHeight(1.f)
		[
			QuitGameButton->AsShared()
		];

	RootBox->SetHeightOverride(200.f);
}

void SKlGameMenuWidget::ResetMenu()
{
	VertBox->ClearChildren();

	for (TArray<TSharedPtr<SCompoundWidget>>::TIterator It(MenuItemList); It; ++It)
	{
		VertBox->AddSlot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(10.f)
			.FillHeight(1.f)
			[
				(*It)->AsShared()
			];
	}

	RootBox->SetHeightOverride(400.f);

	SaveGameButton->SetVisibility(EVisibility::Visible);

	SaveGameText->SetText(NSLOCTEXT("KlGame", "SaveGame", "SaveGame"));
}

void SKlGameMenuWidget::InitializeWidget()
{
	MenuItemList.Add(
		SNew(SButton)
		.OnClicked(this, &SKlGameMenuWidget::OptionEvent)
		.HAlign(HAlign_Center).VAlign(VAlign_Center)
		[
			SNew(STextBlock)
			.Text(NSLOCTEXT("KlGame", "GameOption", "GameOption"))
			.Font(GameStyle->Font_30)
		]
	);

	MenuItemList.Add(
		SAssignNew(SaveGameButton, SButton)
		.OnClicked(this, &SKlGameMenuWidget::SaveGameEvent)
		.HAlign(HAlign_Center).VAlign(VAlign_Center)
		[
			SAssignNew(SaveGameText, STextBlock)
			.Text(NSLOCTEXT("KlGame", "SaveGame", "SaveGame"))
			.Font(GameStyle->Font_30)
		]
	);

	MenuItemList.Add(
		SNew(SButton)
		.OnClicked(this, &SKlGameMenuWidget::QuitGameEvent)
		.HAlign(HAlign_Center).VAlign(VAlign_Center)
		[
			SNew(STextBlock)
			.Text(NSLOCTEXT("KlGame", "QuitGame", "QuitGame"))
			.Font(GameStyle->Font_30)
		]
	);

	OptionItemList.Add(
		SNew(SKlGameOptionWidget)
		.ChangeCulture(this, &SKlGameMenuWidget::ChangeCulture)
		.ChangeVolume(this, &SKlGameMenuWidget::ChangeVolume)
	);

	OptionItemList.Add(
		SNew(SButton)
		.OnClicked(this, &SKlGameMenuWidget::GoBackEvent)
		.HAlign(HAlign_Center).VAlign(VAlign_Center)
		[
			SNew(STextBlock)
			.Text(NSLOCTEXT("KlGame", "GoBack", "GoBack"))
			.Font(GameStyle->Font_30)
		]
	);

	SAssignNew(QuitGameButton, SButton)
		.OnClicked(this, &SKlGameMenuWidget::QuitGameEvent)
		.HAlign(HAlign_Center).VAlign(VAlign_Center)
		[
			SNew(STextBlock)
			.Text(NSLOCTEXT("KlGame", "QuitGame", "QuitGame"))
			.Font(GameStyle->Font_30)
		];

	for (TArray<TSharedPtr<SCompoundWidget>>::TIterator It(MenuItemList); It; ++It)
	{
		VertBox->AddSlot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(10.f)
			.FillHeight(1.f)
			[
				(*It)->AsShared()
			];
	}

}

FReply SKlGameMenuWidget::OptionEvent()
{
	VertBox->ClearChildren();

	VertBox->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(10.f)
		.FillHeight(3.2f)
		[
			OptionItemList[0]->AsShared()
		];

		VertBox->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(10.f)
		.FillHeight(1.f)
		[
			OptionItemList[1]->AsShared()
		];

	RootBox->SetHeightOverride(520.f);
	return FReply::Handled();
}

FReply SKlGameMenuWidget::SaveGameEvent()
{
	SaveGameDele.ExecuteIfBound();

	SaveGameButton->SetVisibility(EVisibility::HitTestInvisible);

	SaveGameText->SetText(NSLOCTEXT("KlGame", "SaveCompleted", "SaveCompleted"));

	return FReply::Handled();
}

FReply SKlGameMenuWidget::QuitGameEvent()
{
	Cast<AKlPlayerController>(UGameplayStatics::GetPlayerController(GWorld, 0))->ConsoleCommand("quit");

	return FReply::Handled();
}

FReply SKlGameMenuWidget::GoBackEvent()
{
	VertBox->ClearChildren();

	for (TArray<TSharedPtr<SCompoundWidget>>::TIterator It(MenuItemList); It; ++It)
	{
		VertBox->AddSlot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(10.f)
			.FillHeight(1.f)
			[
				(*It)->AsShared()
			];
	}

	RootBox->SetHeightOverride(400.f);
	return FReply::Handled();
}

void SKlGameMenuWidget::ChangeCulture(ECultureTeam Culture)
{
	FKlDataHandle::Get()->ChangeLocalizationCulture(Culture);
}

void SKlGameMenuWidget::ChangeVolume(const float MusicVolume, const float SoundVolume)
{
	FKlDataHandle::Get()->ResetGameVolume(MusicVolume, SoundVolume);
}
