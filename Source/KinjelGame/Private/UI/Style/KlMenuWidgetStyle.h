// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateWidgetStyle.h"
#include "SlateWidgetStyleContainerBase.h"
#include "SlateFontInfo.h"
#include "KlMenuWidgetStyle.generated.h"

/**
 * 
 */
USTRUCT()
struct FKlMenuStyle : public FSlateWidgetStyle
{
	GENERATED_USTRUCT_BODY()

	FKlMenuStyle();
	virtual ~FKlMenuStyle();

	// FSlateWidgetStyle
	virtual void GetResources(TArray<const FSlateBrush*>& OutBrushes) const override;
	static const FName TypeName;
	virtual const FName GetTypeName() const override { return TypeName; };
	static const FKlMenuStyle& GetDefault();

	/**
	 * HUD background image brush.
	 */
	UPROPERTY(EditAnywhere, Category = "HUD")
	FSlateBrush MenuHUDBackgroundBrush;

	/**
	* Menu background image brush.
	*/
	UPROPERTY(EditAnywhere, Category = "Menu")
	FSlateBrush MenuBackgroundBrush;

	/**
	* Left icon brush in menu.
	*/
	UPROPERTY(EditAnywhere, Category = "Menu")
	FSlateBrush LeftIconBrush;

	/**
	* Right icon brush in menu.
	*/
	UPROPERTY(EditAnywhere, Category = "Menu")
	FSlateBrush RightIconBrush;

	/**
	* Title border brush in menu.
	*/
	UPROPERTY(EditAnywhere, Category = "Menu")
	FSlateBrush TitleBorderBrush;

	/**
	* Menu item brush in menu.
	*/
	UPROPERTY(EditAnywhere, Category = "Menu Item")
	FSlateBrush MenuItemBrush;

	/**
	* Game option menu background brush.
	*/
	UPROPERTY(EditAnywhere, Category = "Game Option")
	FSlateBrush GameOptionBGBrush;

	/*
	* CheckedBox brush when checked.
	*/
	UPROPERTY(EditAnywhere, Category = "Game Option")
	FSlateBrush CheckedBoxBrush;

	/*
	* Slider bar background brush in GameOption Menu.
	*/
	UPROPERTY(EditAnywhere, Category = "Game Option")
	FSlateBrush SliderBarBrush;

	/*
	* Slider Style 
	*/
	UPROPERTY(EditAnywhere, Category = "Game Option")
	FSliderStyle SliderStyle;

	/*
	* CheckedBox brush when unchecked
	*/
	UPROPERTY(EditAnywhere, Category = "Game Option")
	FSlateBrush UnCheckedBoxBrush;

	/**
	* Font of 60 size in menu.
	*/
	UPROPERTY(EditAnywhere, Category = "Common")
	FSlateFontInfo Font_60;

	/**
	* Font of 40 size in menu.
	*/
	UPROPERTY(EditAnywhere, Category = "Common")
	FSlateFontInfo Font_40;

	/**
	* Font of 30 size in menu.
	*/
	UPROPERTY(EditAnywhere, Category = "Common")
	FSlateFontInfo Font_30;

	/*
	* Color of Black
	*/
	UPROPERTY(EditAnywhere, Category = "Common")
	FLinearColor FontColor_Black;

	/*
	* Color of White
	*/
	UPROPERTY(EditAnywhere, Category = "Common")
	FLinearColor FontColor_White;
};

/**
 */
UCLASS(hidecategories=Object, MinimalAPI)
class UKlMenuWidgetStyle : public USlateWidgetStyleContainerBase
{
	GENERATED_BODY()

public:
	/** The actual data describing the widget appearance. */
	UPROPERTY(Category=Appearance, EditAnywhere, meta=(ShowOnlyInnerProperties))
	FKlMenuStyle WidgetStyle;

	virtual const struct FSlateWidgetStyle* const GetStyle() const override
	{
		return static_cast< const struct FSlateWidgetStyle* >( &WidgetStyle );
	}
};
