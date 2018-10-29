// Fill out your copyright notice in the Description page of Project Settings.

#include "SKlMenuWidget.h"

#include "UI/Style/KlStyle.h"
#include "UI/Style/KlMenuWidgetStyle.h"
#include "SKlMenuItemWidget.h"
#include "SKlNewGameWidget.h"
#include "SKlChooseRecordWidget.h"
#include "SKlGameOptionWidget.h"

#include "Common/FKlHelper.h"
#include "Data/FKlDataHandle.h"

#include "SlateOptMacros.h"
#include "SImage.h"
#include "SOverlay.h"
#include "VerticalBox.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SKlMenuWidget::Construct(const FArguments& InArgs)
{
	// Get Style of the editor
	MenuStyle = &KlStyle::Get().GetWidgetStyle<FKlMenuStyle>("BPKlMenuStyle");

	ChildSlot
		[
			SAssignNew(RootSizeBox, SBox)
			[
				SNew(SOverlay)
				+ SOverlay::Slot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(FMargin(0.f, 50.f, 0.f, 0.f))
		[
			SNew(SImage)
			.Image(&MenuStyle->MenuBackgroundBrush)
		]
	+ SOverlay::Slot()
		.HAlign(HAlign_Left)
		.VAlign(VAlign_Center)
		.Padding(FMargin(0.f, 25.f, 0.f, 0.f))
		[
			SNew(SImage)
			.Image(&MenuStyle->LeftIconBrush)
		]
	+ SOverlay::Slot()
		.HAlign(HAlign_Right)
		.VAlign(VAlign_Center)
		.Padding(FMargin(0.f, 25.f, 0.f, 0.f))
		[
			SNew(SImage)
			.Image(&MenuStyle->RightIconBrush)
		]
	+ SOverlay::Slot()
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Top)
		[
			SNew(SBox)
			.WidthOverride(400.f)
		.HeightOverride(100.f)
		[
			SNew(SBorder)
			.BorderImage(&MenuStyle->TitleBorderBrush)
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		[
			SAssignNew(TitleText, STextBlock)
			.Font(KlStyle::Get().GetFontStyle("MenuItemFont"))
		.Text(NSLOCTEXT("KlMenu", "Menu", "Menu"))
		]
		]
		]
	+ SOverlay::Slot()
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Top)
		.Padding(FMargin(0.f, 130.f, 0.f, 0.f))
		[
			SAssignNew(ContentBox, SVerticalBox)
		]
			]
		];

	// Initialize all menus.
	InitializeMenuList();

	InitializedAnimation();
}

void SKlMenuWidget::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	switch (AnimState)
	{
	case EMenuAnim::Stop:
		break;
	case EMenuAnim::Close:
		// If playing
		if (MenuAnimation.IsPlaying()) {
			// Change menu's size in real time
			ResetWidgetSize(MenuCurve.GetLerp() * 600.f, -1.f);
			// Hide menu when close to 40%
			if (MenuCurve.GetLerp() < 0.6f && IsMenuShow) ChooseWidget(EMenuType::None);
		}
		else {
			// If animation palyed, change state
			AnimState = EMenuAnim::Open;
			// Play Open Animation
			MenuAnimation.Play(this->AsShared());
		}
		break;
	case EMenuAnim::Open:
		// If playing
		if (MenuAnimation.IsPlaying())
		{
			// Change menu's size in real time
			ResetWidgetSize(MenuCurve.GetLerp() * 600.f, CurrentHeight);
			// Display widget when open 60%
			if (MenuCurve.GetLerp() > 0.6f && !IsMenuShow) ChooseWidget(CurrentMenu);
		}
		// If Animation played.
		if (MenuAnimation.IsAtEnd())
		{
			// Change state to stop
			AnimState = EMenuAnim::Stop;
			// Unlocked.
			ControlLocked = false;
		}
		break;
	}
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SKlMenuWidget::MenuItemOnClicked(EMenuItem::Type ItemType)
{
	// If Controller locked, return
	if (ControlLocked) return;
	// Set controller to lock
	ControlLocked = true;

	switch (ItemType)
	{
	case EMenuItem::StartGame:
		PlayClose(EMenuType::StartGame);
		break;
	case EMenuItem::GameOption:
		PlayClose(EMenuType::GameOption);
		break;
	case EMenuItem::QuitGame:
		// Quit game, play sound and delay call quitfunc.
		//FKlHelper::PlayerSoundAndCall(UGameplayStatics::GetPlayerController(GWorld, 0)->GetWorld(), MenuStyle->ExitGameSound, this, &SSlAiMenuWidget::QuitGame);
		break;
	case EMenuItem::NewGame:
		PlayClose(EMenuType::NewGame);
		break;
	case EMenuItem::LoadRecord:
		PlayClose(EMenuType::ChooseRecord);
		break;
	case EMenuItem::StartGameGoBack:
		PlayClose(EMenuType::MainMenu);
		break;
	case EMenuItem::GameOptionGoBack:
		PlayClose(EMenuType::MainMenu);
		break;
	case EMenuItem::NewGameGoBack:
		PlayClose(EMenuType::StartGame);
		break;
	case EMenuItem::ChooseRecordGoBack:
		PlayClose(EMenuType::StartGame);
		break;
	case EMenuItem::EnterGame:
		// Allow to enter game?
		if (NewGameWidget->AllowEnterGame())
		{
			//FKlHelper::PlayerSoundAndCall(UGameplayStatics::GetPlayerController(GWorld, 0)->GetWorld(), MenuStyle->StartGameSound, this, &SSlAiMenuWidget::EnterGame);
		}
		else
		{
			// Unlocked
			ControlLocked = false;
		}
		break;
	case EMenuItem::EnterRecord:
		ChooseRecordWidget->UpdateRecordName();
		//FKlHelper::PlayerSoundAndCall(UGameplayStatics::GetPlayerController(GWorld, 0)->GetWorld(), MenuStyle->StartGameSound, this, &SSlAiMenuWidget::EnterGame);
		break;
	}
}

void SKlMenuWidget::ChangeCulture(ECultureTeam Culture)
{
	FKlDataHandle::Get()->ChangeLocalizationCulture(Culture);
}

void SKlMenuWidget::ChangeVolume(const float MusicVolume, const float SoundVolume)
{
	FKlDataHandle::Get()->ResetMenuVolume(MusicVolume, SoundVolume);
}

void SKlMenuWidget::InitializeMenuList()
{
	// Initialize main menu
	TArray<TSharedPtr<SCompoundWidget>> MainMenuList;
	MainMenuList.Add(
		SNew(SKlMenuItemWidget)
		.ItemText(NSLOCTEXT("KlMenu", "StartGame", "StartGame"))
		.ItemType(EMenuItem::StartGame)
		.OnClicked(this, &SKlMenuWidget::MenuItemOnClicked)
	);
	MainMenuList.Add(
		SNew(SKlMenuItemWidget)
		.ItemText(NSLOCTEXT("KlMenu", "GameOption", "GameOption"))
		.ItemType(EMenuItem::GameOption)
		.OnClicked(this, &SKlMenuWidget::MenuItemOnClicked)
	);
	MainMenuList.Add(
		SNew(SKlMenuItemWidget)
		.ItemText(NSLOCTEXT("KlMenu", "QuitGame", "QuitGame"))
		.ItemType(EMenuItem::QuitGame)
		.OnClicked(this, &SKlMenuWidget::MenuItemOnClicked)
	);

	MenuMap.Add(
		EMenuType::MainMenu,
		MakeShareable(new MenuGroup(NSLOCTEXT("KlMenu", "Menu", "Menu"), 510.f, &MainMenuList))
	);

	// Initialize Start Game Menu.
	TArray<TSharedPtr<SCompoundWidget>> StartGameList;
	StartGameList.Add(
		SNew(SKlMenuItemWidget)
		.ItemText(NSLOCTEXT("KlMenu", "NewGame", "NewGame"))
		.ItemType(EMenuItem::NewGame)
		.OnClicked(this, &SKlMenuWidget::MenuItemOnClicked)
	);
	StartGameList.Add(
		SNew(SKlMenuItemWidget)
		.ItemText(NSLOCTEXT("KlMenu", "LoadRecord", "LoadRecord"))
		.ItemType(EMenuItem::LoadRecord).OnClicked(this, &SKlMenuWidget::MenuItemOnClicked)
	);
	StartGameList.Add(
		SNew(SKlMenuItemWidget)
		.ItemText(NSLOCTEXT("KlMenu", "GoBack", "GoBack"))
		.ItemType(EMenuItem::StartGameGoBack)
		.OnClicked(this, &SKlMenuWidget::MenuItemOnClicked)
	);

	MenuMap.Add(
		EMenuType::StartGame,
		MakeShareable(new MenuGroup(NSLOCTEXT("KlMenu", "StartGame", "StartGame"), 510.f, &StartGameList))
	);

	// Initialize Game Option Menu
	TArray<TSharedPtr<SCompoundWidget>> GameOptionList;

	SAssignNew(GameOptionWidget, SKlGameOptionWidget)
		.ChangeCulture(this, &SKlMenuWidget::ChangeCulture)
		.ChangeVolume(this, &SKlMenuWidget::ChangeVolume);

	GameOptionList.Add(GameOptionWidget);
	GameOptionList.Add(SNew(SKlMenuItemWidget)
		.ItemText(NSLOCTEXT("KlMenu", "GoBack", "GoBack"))
		.ItemType(EMenuItem::GameOptionGoBack)
		.OnClicked(this, &SKlMenuWidget::MenuItemOnClicked));

	MenuMap.Add(
		EMenuType::GameOption,
		MakeShareable(new MenuGroup(NSLOCTEXT("KlMenu", "GameOption", "GameOption"), 610.f, &GameOptionList))
	);

	// Initialize New Game Menu
	TArray<TSharedPtr<SCompoundWidget>> NewGameList;
	SAssignNew(NewGameWidget, SKlNewGameWidget);

	NewGameList.Add(NewGameWidget);

	NewGameList.Add(SNew(SKlMenuItemWidget)
		.ItemText(NSLOCTEXT("KlMenu", "EnterGame", "EnterGame"))
		.ItemType(EMenuItem::EnterGame)
		.OnClicked(this, &SKlMenuWidget::MenuItemOnClicked));

	NewGameList.Add(SNew(SKlMenuItemWidget)
		.ItemText(NSLOCTEXT("KlMenu", "GoBack", "GoBack"))
		.ItemType(EMenuItem::NewGameGoBack)
		.OnClicked(this, &SKlMenuWidget::MenuItemOnClicked));

	MenuMap.Add(
		EMenuType::NewGame,
		MakeShareable(new MenuGroup(NSLOCTEXT("KlMenu", "NewGame", "NewGame"), 510.f, &NewGameList))
	);

	// Initialize Choose Record Menu
	TArray<TSharedPtr<SCompoundWidget>> ChooseRecordList;
	SAssignNew(ChooseRecordWidget, SKlChooseRecordWidget);

	ChooseRecordList.Add(ChooseRecordWidget);

	ChooseRecordList.Add(SNew(SKlMenuItemWidget)
		.ItemText(NSLOCTEXT("KlMenu", "EnterRecord", "EnterRecord"))
		.ItemType(EMenuItem::EnterRecord)
		.OnClicked(this, &SKlMenuWidget::MenuItemOnClicked));

	ChooseRecordList.Add(SNew(SKlMenuItemWidget)
		.ItemText(NSLOCTEXT("KlMenu", "GoBack", "GoBack"))
		.ItemType(EMenuItem::ChooseRecordGoBack)
		.OnClicked(this, &SKlMenuWidget::MenuItemOnClicked));

	MenuMap.Add(
		EMenuType::ChooseRecord,
		MakeShareable(new MenuGroup(NSLOCTEXT("KlMenu", "LoadRecord", "LoadRecord"), 510.f, &ChooseRecordList))
	);

	// Display main menu by default.
	ChooseWidget(EMenuType::MainMenu);
}

void SKlMenuWidget::ChooseWidget(EMenuType::Type WidgetType)
{
	// Whether menu show
	IsMenuShow = WidgetType != EMenuType::None;

	// Remove all current widgets
	ContentBox->ClearChildren();

	// If WidgetType is null
	if (WidgetType == EMenuType::None) return;

	// Add widgets
	for (TArray<TSharedPtr<SCompoundWidget>>::TIterator It((*MenuMap.Find(WidgetType))->ChildWidget); It; It++) {
		ContentBox->AddSlot()
			.AutoHeight()
			[
				(*It)->AsShared()
			];
	}

	// Change Menu Title
	TitleText->SetText((*MenuMap.Find(WidgetType))->MenuName);

	ResetWidgetSize(600.f, (*MenuMap.Find(WidgetType))->MenuHeight);
}

void SKlMenuWidget::ResetWidgetSize(float NewWidget, float NewHeight)
{
	RootSizeBox->SetWidthOverride(NewWidget);

	if (NewHeight < 0) return;
	RootSizeBox->SetHeightOverride(NewHeight);
}

void SKlMenuWidget::InitializedAnimation()
{
	// Delay time
	const float StartDelay = 0.3f;
	// Time duration
	const float AnimDuration = 0.6f;
	MenuAnimation = FCurveSequence();
	MenuCurve = MenuAnimation.AddCurve(StartDelay, AnimDuration, ECurveEaseFunction::QuadInOut);
	// Menu size
	ResetWidgetSize(600.f, 510.f);
	// Show main menu
	ChooseWidget(EMenuType::MainMenu);
	// Allow button to clicked
	ControlLocked = false;
	// Anim state
	AnimState = EMenuAnim::Stop;
	// Set Animation to the end, is 1.
	MenuAnimation.JumpToEnd();
}

void SKlMenuWidget::PlayClose(EMenuType::Type NewMenu)
{
	CurrentMenu = NewMenu;

	CurrentHeight = (*MenuMap.Find(NewMenu))->MenuHeight;

	// Current state is closed.
	AnimState = EMenuAnim::Close;

	// From 1 to 0.
	MenuAnimation.PlayReverse(this->AsShared());

	//FSlateApplication::Get().PlaySound(MenuStyle->MenuItemChangeSound);
}
