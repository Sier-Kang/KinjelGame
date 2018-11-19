// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateWidgetStyle.h"
#include "SlateWidgetStyleContainerBase.h"

#include "KlGameWidgetStyle.generated.h"

/**
 * 
 */
USTRUCT()
struct FKlGameStyle : public FSlateWidgetStyle
{
	GENERATED_USTRUCT_BODY()

	FKlGameStyle();
	virtual ~FKlGameStyle();

	// FSlateWidgetStyle
	virtual void GetResources(TArray<const FSlateBrush*>& OutBrushes) const override;
	static const FName TypeName;
	virtual const FName GetTypeName() const override { return TypeName; };
	static const FKlGameStyle& GetDefault();

	// Grid Panel with shotcut brush default
	UPROPERTY(EditAnywhere, Category = "Package")
	FSlateBrush NormalContainerBrush;

	// Grid Panel with shotcut brush when choose
	UPROPERTY(EditAnywhere, Category = "Package")
	FSlateBrush ChoosedContainerBrush;

	// Empty contain Brush
	UPROPERTY(EditAnywhere, Category = "Package")
	FSlateBrush EmptyBrush;

	// Package BG Brush
	UPROPERTY(EditAnywhere, Category = "Package")
	FSlateBrush PackageBGBrush;

	// Compositor Arrow Brush
	UPROPERTY(EditAnywhere, Category = "Package")
	FSlateBrush CompoundArrowBrush;

	// Object texture brush
	UPROPERTY(EditAnywhere, Category = "Package")
	FSlateBrush ObjectBrush_1;

	UPROPERTY(EditAnywhere, Category = "Package")
	FSlateBrush ObjectBrush_2;

	UPROPERTY(EditAnywhere, Category = "Package")
	FSlateBrush ObjectBrush_3;

	UPROPERTY(EditAnywhere, Category = "Package")
	FSlateBrush ObjectBrush_4;

	UPROPERTY(EditAnywhere, Category = "Package")
	FSlateBrush ObjectBrush_5;

	UPROPERTY(EditAnywhere, Category = "Package")
	FSlateBrush ObjectBrush_6;

	UPROPERTY(EditAnywhere, Category = "Package")
	FSlateBrush ObjectBrush_7;

	/**
	* Object name that ray cast
	*/
	UPROPERTY(EditAnywhere, Category = "RayCast")
	FSlateBrush RayInfoBrush;

	/**
	* Pointer insight brush
	*/
	UPROPERTY(EditAnywhere, Category = "RayCast")
	FSlateBrush PointerBrush;

	/** MiniMap background brush */
	UPROPERTY(EditAnywhere, Category = "MiniMap")
	FSlateBrush MiniMapBGBrush;

	// Character icon in mini map
	UPROPERTY(EditAnywhere, Category = "MiniMap")
	FSlateBrush PawnPointBrush;

	// Player state background
	UPROPERTY(EditAnywhere, Category = "PlayerState")
	FSlateBrush PlayerStateBGBrush;

	// Background image of character's head
	UPROPERTY(EditAnywhere, Category = "PlayerState")
	FSlateBrush PlayerHeadBGBrush;

	// HP Brush
	UPROPERTY(EditAnywhere, Category = "PlayerState")
	FSlateBrush HPBrush;

	// Hungry Brush
	UPROPERTY(EditAnywhere, Category = "PlayerState")
	FSlateBrush HungerBrush;

	// Player character's head
	UPROPERTY(EditAnywhere, Category = "PlayerState")
	FSlateBrush PlayerHeadBrush;

	/*
	* Font of 60
	*/
	UPROPERTY(EditAnywhere, Category = "Common")
	FSlateFontInfo Font_60;

	/*
	* Font of 50 with outline
	*/
	UPROPERTY(EditAnywhere, Category = "Common")
	FSlateFontInfo Font_Outline_50;

	/*
	* Font of 40
	*/
	UPROPERTY(EditAnywhere, Category = "Common")
	FSlateFontInfo Font_40;

	/*
	* Font of 40 with outline
	*/
	UPROPERTY(EditAnywhere, Category = "Common")
	FSlateFontInfo Font_Outline_40;

	/*
	* Font of 30
	*/
	UPROPERTY(EditAnywhere, Category = "Common")
		FSlateFontInfo Font_30;

	/*
	* Font of 20
	*/
	UPROPERTY(EditAnywhere, Category = "Common")
	FSlateFontInfo Font_20;

	/*
	* Font of 20 with outline
	*/
	UPROPERTY(EditAnywhere, Category = "Common")
	FSlateFontInfo Font_Outline_20;

	/*
	* Font of 16 with outline
	*/
	UPROPERTY(EditAnywhere, Category = "Common")
	FSlateFontInfo Font_Outline_16;

	/*
	* Font of 16
	*/
	UPROPERTY(EditAnywhere, Category = "Common")
	FSlateFontInfo Font_16;

	/*
	* White color
	*/
	UPROPERTY(EditAnywhere, Category = "Common")
	FLinearColor FontColor_White;

	/*
	* Black color
	*/
	UPROPERTY(EditAnywhere, Category = "Common")
	FLinearColor FontColor_Black;
};

/**
 */
UCLASS(hidecategories=Object, MinimalAPI)
class UKlGameWidgetStyle : public USlateWidgetStyleContainerBase
{
	GENERATED_BODY()

public:
	/** The actual data describing the widget appearance. */
	UPROPERTY(Category=Appearance, EditAnywhere, meta=(ShowOnlyInnerProperties))
	FKlGameStyle WidgetStyle;

	virtual const struct FSlateWidgetStyle* const GetStyle() const override
	{
		return static_cast< const struct FSlateWidgetStyle* >( &WidgetStyle );
	}
};
