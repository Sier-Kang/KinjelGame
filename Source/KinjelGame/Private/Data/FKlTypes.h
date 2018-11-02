// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * Culture type
 */
UENUM()
enum class ECultureTeam : uint8 
{
	EN = 0,
	ZH
};

/**
* Menu button type
*/
namespace EMenuItem 
{
	enum Type
	{
		None,
		StartGame,
		GameOption,
		QuitGame,

		NewGame,
		LoadRecord,

		StartGameGoBack,
		GameOptionGoBack,
		NewGameGoBack,
		ChooseRecordGoBack,
		EnterGame,
		EnterRecord,
	};
}

/**
* Menu type
*/
namespace EMenuType
{
	enum Type
	{   
		None,
		MainMenu,
		StartGame,
		GameOption,
		NewGame,
		ChooseRecord
	};
}

/**
* Menu Animation State
*/
namespace EMenuAnim
{
	enum Type
	{
		Stop, // Stop Animation
		Close, // Close Menu
		Open  // OpenMenu
	};
}

/**
* View Mode
*/
namespace EGameViewMode
{
	enum Type
	{
		First,
		Third
	};
}

/**
* Character upper body animation status.
*/
namespace EUpperBody
{
	enum Type
	{
		None,
		Punch,
		Hit,
		Fight,
		PickUp,
		Eat
	};
}