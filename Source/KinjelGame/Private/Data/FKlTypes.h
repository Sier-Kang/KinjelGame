// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SBorder.h"
#include "STextBlock.h"
#include "SlateBrush.h"

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

/**
* Shotcut container struct
*/
struct ShotcutContainer
{
	// Object ID
	int ObjectIndex;
	int ObjectNum;

	TSharedPtr<class SBorder> ContainerBorder;
	TSharedPtr<SBorder> ObjectImage;
	TSharedPtr<STextBlock> ObjectNumText;

	const FSlateBrush* NormalContainerBrush;
	const FSlateBrush* ChoosedContainerBrush;
	TArray<const FSlateBrush*>* ObjectBrushList;

	ShotcutContainer(TSharedPtr<SBorder> CB, TSharedPtr<SBorder> OI, TSharedPtr<STextBlock> ONT,
		const FSlateBrush* NCB, const FSlateBrush* CCB, TArray<const FSlateBrush*>* OBL)
	{
		ContainerBorder = CB;
		ObjectImage = OI;
		ObjectNumText = ONT;
		NormalContainerBrush = NCB;
		ChoosedContainerBrush = CCB;
		ObjectBrushList = OBL;

		// Initialize display settings
		ObjectIndex = 0;
		ObjectNum = 0;
		ContainerBorder->SetBorderImage(NormalContainerBrush);
		ObjectImage->SetBorderImage((*ObjectBrushList)[0]);
	}

	// Whether choose current object, choose is true, unchoose is false
	int SetChoosed(bool Option)
	{
		if (Option)
		{
			ContainerBorder->SetBorderImage(ChoosedContainerBrush);
		}
		else {
			ContainerBorder->SetBorderImage(NormalContainerBrush);
		}
		return ObjectIndex;
	}

	// Set Index
	ShotcutContainer* SetObject(int NewIndex)
	{
		ObjectIndex = NewIndex;
		ObjectImage->SetBorderImage((*ObjectBrushList)[ObjectIndex]);
		return this;
	}

	// Set number
	ShotcutContainer* SetObjectNum(int Num = 0)
	{
		ObjectNum = Num;
		// If number is 0 or 1, undisplay number
		if (ObjectNum == 0 || ObjectNum == 1) {
			ObjectNumText->SetText(FString(""));
		}
		else {
			ObjectNumText->SetText(FString::FromInt(ObjectNum));
		}

		return this;
	}
};

// Resource type
namespace EResourceType
{
	enum Type
	{
		Plant = 0,
		Metal,
		Animal
	};
}

/**
* Resource Attribute Struct
*/
struct ResourceAttribute
{
	FText EN;// English name
	FText ZH;// Chinese name
	EResourceType::Type ResourceType;
	int HP;
	TArray<TArray<int>> FlobObjectInfo;

	ResourceAttribute(const FText ENName, const FText ZHName, const EResourceType::Type RT, 
		const int HPValue, TArray<TArray<int>>* FOI)
	{
		EN = ENName;
		ZH = ZHName;
		ResourceType = RT;
		HP = HPValue;

		// Deep copy
		for (TArray<TArray<int>>::TIterator It(*FOI); It; ++It) {
			TArray<int> FlobObjectInfoItem;
			for (TArray<int>::TIterator Ih(*It); Ih; ++Ih) {
				FlobObjectInfoItem.Add(*Ih);
			}
			FlobObjectInfo.Add(FlobObjectInfoItem);
		}
	}


	FString ToString()
	{
		FString InfoStr;
		for (TArray<TArray<int>>::TIterator It(FlobObjectInfo); It; ++It) {
			for (TArray<int>::TIterator Ih(*It); Ih; ++Ih) {
				InfoStr += FString::FromInt(*Ih) + FString(".");
			}
			InfoStr += FString("__");
		}
		return EN.ToString() + FString("--") + ZH.ToString() + FString("--") + FString::FromInt((int)ResourceType) + FString("--") + FString::FromInt(HP) + FString("--") + InfoStr;
	}
};

/**
* Game menu type
*/
namespace EGameUIType
{
	enum Type
	{
		Game, // Game mode
		Pause, // Game pause
		Lose, // Player dead
		Package, // Player's package
		ChatRoom // Chat room, between player and enemy
	};
}