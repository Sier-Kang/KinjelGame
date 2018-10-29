// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Data/FKlTypes.h"

/**
* Menu Info
*/
struct MenuGroup
{
	// Menu Title
	FText MenuName;

	// Menu Height
	float MenuHeight;

	// sub-widget
	TArray<TSharedPtr<SCompoundWidget>> ChildWidget;

	// Constructor
	MenuGroup(const FText Name, const float Height, TArray<TSharedPtr<SCompoundWidget>>* Children)
	{
		MenuName = Name;
		MenuHeight = Height;

		for (TArray<TSharedPtr<SCompoundWidget>>::TIterator It(*Children); It; It++)
		{
			ChildWidget.Add(*It);
		}
	}
};

/**
 * 
 */
class SKlMenuWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SKlMenuWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	/** Tick */
	void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;

private:
	/**
	* Item click event.
	* @params Item type
	* @return
	*/
	void MenuItemOnClicked(EMenuItem::Type ItemType);

	/**
	* Change Culture
	* @params Culture type
	* @return
	*/
	void ChangeCulture(ECultureTeam Culture);

	/**
	* Change Musici and Sound
	* @params 
	* @return
	*/
	void ChangeVolume(const float MusicVolume, const float SoundVolume);

	/**
	* Initialize all menus.
	*/
	void InitializeMenuList();

	/**
	* Switch control of menus
	*/
	void ChooseWidget(EMenuType::Type WidgetType);

	/**
	* Resize menu's size.
	*/
	void ResetWidgetSize(float NewWidget, float NewHeight);

	/**
	* Initialize menu animation
	*/
	void InitializedAnimation();

	/**
	* Play close animation
	*/
	void PlayClose(EMenuType::Type NewMenu);

private:
	/** Size box of the menu */
	TSharedPtr<SBox> RootSizeBox;

	/** Title Text */
	TSharedPtr<STextBlock> TitleText;

	/** Get the style of menu */
	const struct FKlMenuStyle* MenuStyle;

	/** To save vertical list */
	TSharedPtr<SVerticalBox> ContentBox;

	// Menu Group
	TMap<EMenuType::Type, TSharedPtr<MenuGroup>> MenuMap;

	/** Game option widget */
	TSharedPtr<class SKlGameOptionWidget> GameOptionWidget;

	/** New game widget */
	TSharedPtr<class SKlNewGameWidget> NewGameWidget;

	/** Choose record widget */
	TSharedPtr<class SKlChooseRecordWidget> ChooseRecordWidget;

	/** Menu Animations about */
	FCurveSequence MenuAnimation;

	FCurveHandle MenuCurve;

	float CurrentHeight;

	bool IsMenuShow;

	bool ControlLocked;

	/** Save current menu animation state */
	EMenuAnim::Type AnimState;

	/** Save current menu */
	EMenuType::Type CurrentMenu;
};
