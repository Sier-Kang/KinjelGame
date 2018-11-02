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

/**
* Type of object
*/
namespace EObjectType
{
	enum Type
	{
		Normal = 0, // Wood/Stone
		Food, // Apple/Meat
		Tool, // Hammer/Axe
		Weapon // Sword
	};
}
/**
* Object Information
*/
struct ObjectAttribute
{
	FText EN; // English name
	FText ZH; // Chinese name
	EObjectType::Type ObjectType; // Object type
	int PlantAttack; // Attack value to plants
	int MetalAttack; // Attack value to metal
	int AnimalAttack; // Attack value to animal
	int AffectRange; // Distance that attack can effect
	FString TexPath; // Texture path

	// Constructor
	ObjectAttribute(const FText ENName, const FText ZHName, const EObjectType::Type OT, const int PA, const int MA,
		const int AA, const int AR, const FString TP)
	{
		EN = ENName;
		ZH = ZHName;
		ObjectType = OT;
		PlantAttack = PA;
		MetalAttack = MA;
		AnimalAttack = AA;
		AffectRange = AR;
		TexPath = TP;
	}
};