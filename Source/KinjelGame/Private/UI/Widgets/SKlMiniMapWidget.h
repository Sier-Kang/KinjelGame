// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SlateBasics.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class SKlMiniMapWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SKlMiniMapWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	/** Override OnPaint function */
	virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;

	/** Receive texture resource from GameMode */
	void RegisterMiniMap(class UTextureRenderTarget2D* MiniMapRender);

	/** Receive player's information from GameMode, bind delegate UpdateMapDirection of GameMode */
	void UpdateMapData(const FRotator PlayerRotator, const float MiniMapSize, const TArray<FVector2D>* EnemyPosList, const TArray<bool>* EnemyLockList, const TArray<float>* EnemyRotateList);
private:
	/** Game style */
	const struct FKlGameStyle* GameStyle;

	/** MiniMap Image */
	TSharedPtr<SImage> MiniMapImage;

	/** Enemy view image */
	TSharedPtr<SImage> EnemyViewImage;

	/** Enemy view material */
	class UMaterialInstanceDynamic* EnemyViewMatDynamic;

	struct FSlateBrush* MiniMapBrush;

	/** Render position of four directions */
	FVector2D NorthLocation;
	FVector2D SouthLocation;
	FVector2D EastLocation;
	FVector2D WestLocation;

	/** Size of mini map*/
	float MapSize;

	/** Enemy's position according to player */
	TArray<FVector2D> EnemyPos;

	/** Flag of weather enemies lock player */
	TArray<bool> EnemyLock;
};
