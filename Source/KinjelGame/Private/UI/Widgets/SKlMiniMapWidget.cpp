// Fill out your copyright notice in the Description page of Project Settings.

#include "SKlMiniMapWidget.h"
#include "SlateOptMacros.h"
#include "UI/Style/KlStyle.h"
#include "UI/Style/KlGameWidgetStyle.h"
#include "Materials/MaterialInterface.h"
#include "SOverlay.h"
#include "SImage.h"
#include "DrawElements.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "SlateBrush.h"
#include "Engine/TextureRenderTarget2D.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SKlMiniMapWidget::Construct(const FArguments& InArgs)
{
	GameStyle = &KlStyle::Get().GetWidgetStyle<FKlGameStyle>("BPKlGameStyle");

	ChildSlot
	[
		SNew(SBox)
		.WidthOverride(320.f)
		.HeightOverride(320.f)
		[
			SNew(SOverlay)
			//MiniMap background image
			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SImage)
				.Image(&GameStyle->MiniMapBGBrush)
			]

			// Render MiniMap
			+ SOverlay::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SAssignNew(MiniMapImage, SImage)
			]

			// Render enemy view image
			+ SOverlay::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SAssignNew(EnemyViewImage, SImage)
			]
		]
	];
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

int32 SKlMiniMapWidget::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	SCompoundWidget::OnPaint(Args, AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);

	// Render player icon
	FSlateDrawElement::MakeBox(
		OutDrawElements,
		LayerId + 10,
		AllottedGeometry.ToPaintGeometry(FVector2D(155.f, 155.f), FVector2D(10.f, 10.f)),
		&GameStyle->PawnPointBrush,
		ESlateDrawEffect::None,
		FLinearColor(1.f, 1.f, 0.f, 1.f)
	);

	// Render Direction Text
	FSlateDrawElement::MakeText(
		OutDrawElements,
		LayerId + 10,
		AllottedGeometry.ToPaintGeometry(NorthLocation - FVector2D(8.f, 8.f), FVector2D(16.f, 16.f)),
		NSLOCTEXT("SlAiGame", "N", "N"),
		GameStyle->Font_16,
		ESlateDrawEffect::None,
		FLinearColor(1.f, 1.f, 1.f, 1.f)
	);
	FSlateDrawElement::MakeText(
		OutDrawElements,
		LayerId + 10,
		AllottedGeometry.ToPaintGeometry(SouthLocation - FVector2D(8.f, 8.f), FVector2D(16.f, 16.f)),
		NSLOCTEXT("SlAiGame", "S", "S"),
		GameStyle->Font_16,
		ESlateDrawEffect::None,
		FLinearColor(1.f, 1.f, 1.f, 1.f)
	);
	FSlateDrawElement::MakeText(
		OutDrawElements,
		LayerId + 10,
		AllottedGeometry.ToPaintGeometry(EastLocation - FVector2D(8.f, 8.f), FVector2D(16.f, 16.f)),
		NSLOCTEXT("SlAiGame", "E", "E"),
		GameStyle->Font_16,
		ESlateDrawEffect::None,
		FLinearColor(1.f, 1.f, 1.f, 1.f)
	);
	FSlateDrawElement::MakeText(
		OutDrawElements,
		LayerId + 10,
		AllottedGeometry.ToPaintGeometry(WestLocation - FVector2D(8.f, 8.f), FVector2D(16.f, 16.f)),
		NSLOCTEXT("SlAiGame", "W", "W"),
		GameStyle->Font_16,
		ESlateDrawEffect::None,
		FLinearColor(1.f, 1.f, 1.f, 1.f)
	);

	// Render enemy icons
	for (int i = 0; i < EnemyPos.Num(); ++i) {
		FSlateDrawElement::MakeBox(
			OutDrawElements,
			LayerId + 10,
			AllottedGeometry.ToPaintGeometry(EnemyPos[i] - FVector2D(5.f, 5.f), FVector2D(10.f, 10.f)),
			&GameStyle->PawnPointBrush,
			ESlateDrawEffect::None,
			EnemyLock[i] ? FLinearColor(1.f, 0.f, 0.f, 1.f) : FLinearColor(0.f, 1.f, 0.f, 1.f)
		);
	}

	return LayerId;
}

void SKlMiniMapWidget::RegisterMiniMap(UTextureRenderTarget2D* MiniMapRender)
{
	UMaterialInterface* MiniMapMatInst = LoadObject<UMaterialInterface>(
		NULL, 
		TEXT("MaterialInstanceConstant'/Game/Material/MiniMapMatInst.MiniMapMatInst'")
	);

	UMaterialInstanceDynamic* MiniMapMatDynamic = UMaterialInstanceDynamic::Create(MiniMapMatInst, nullptr);

	MiniMapMatDynamic->SetTextureParameterValue(FName("MiniMapTex"), MiniMapRender);

	MiniMapBrush = new FSlateBrush();

	MiniMapBrush->ImageSize = FVector2D(280.f, 280.f);
	MiniMapBrush->DrawAs = ESlateBrushDrawType::Image;

	MiniMapBrush->SetResourceObject(MiniMapMatDynamic);

	MiniMapImage->SetImage(MiniMapBrush);


	UMaterialInterface* EnemyViewMatInst = LoadObject<UMaterialInterface>(
		NULL, 
		TEXT("MaterialInstanceConstant'/Game/Material/EnemyViewMatInst.EnemyViewMatInst'")
	);

	EnemyViewMatDynamic = UMaterialInstanceDynamic::Create(EnemyViewMatInst, nullptr);

	FSlateBrush* EnemyViewBrush = new FSlateBrush();

	EnemyViewBrush->ImageSize = FVector2D(280.f, 280.f);
	EnemyViewBrush->DrawAs = ESlateBrushDrawType::Image;

	EnemyViewBrush->SetResourceObject(EnemyViewMatDynamic);

	EnemyViewImage->SetImage(EnemyViewBrush);

	EnemyViewImage->SetColorAndOpacity(FLinearColor(0.3f, 1.f, 0.32f, 0.4f));
}

void SKlMiniMapWidget::UpdateMapData(const FRotator PlayerRotator, const float MiniMapSize, const TArray<FVector2D>* EnemyPosList, const TArray<bool>* EnemyLockList, const TArray<float>* EnemyRotateList)
{
	float YawDir = -PlayerRotator.Yaw;

	NorthLocation = FVector2D(FMath::Sin(FMath::DegreesToRadians(YawDir)), FMath::Cos(FMath::DegreesToRadians(YawDir))) * 150.f + FVector2D(160.f, 160.f);
	EastLocation = FVector2D(FMath::Sin(FMath::DegreesToRadians(YawDir + 90.f)), FMath::Cos(FMath::DegreesToRadians(YawDir + 90.f)))*150.f + FVector2D(160.f, 160.f);
	SouthLocation = FVector2D(FMath::Sin(FMath::DegreesToRadians(YawDir + 180.f)), FMath::Cos(FMath::DegreesToRadians(YawDir + 180.f)))*150.f + FVector2D(160.f, 160.f);
	WestLocation = FVector2D(FMath::Sin(FMath::DegreesToRadians(YawDir + 270.f)), FMath::Cos(FMath::DegreesToRadians(YawDir + 270.f)))*150.f + FVector2D(160.f, 160.f);

	MapSize = MiniMapSize;

	EnemyPos.Empty();
	EnemyLock.Empty();

	float DPIRatio = 280.f / MapSize;

	TArray<float> EnemyViewRotate;
	TArray<FVector2D> EnemyViewPos;
	TArray<bool> EnemyViewLock;

	for (int i = 0; i < (*EnemyPosList).Num(); ++i) 
	{
		float RealDistance = (*EnemyPosList)[i].Size();
		if (RealDistance * 2 < MapSize)
		{
			EnemyPos.Add((*EnemyPosList)[i] * DPIRatio + FVector2D(160.f, 160.f));

			EnemyLock.Add((*EnemyLockList)[i]);
		}

		if (RealDistance * 2 < MapSize + 2000.f)
		{
			EnemyViewPos.Add((*EnemyPosList)[i] * DPIRatio + FVector2D(160.f, 160.f));
			EnemyViewLock.Add((*EnemyLockList)[i]);

			float RotVal = -(*EnemyRotateList)[i];
			if (RotVal > 180.f) RotVal -= 360.f;
			if (RotVal < -180.f) RotVal += 360.f;

			RotVal += 180.f;
			RotVal /= 360.f;
			RotVal = RotVal + 0.5f > 1.f ? RotVal - 0.5f : RotVal + 0.5f;

			EnemyViewRotate.Add(RotVal);
		}
	}

	int ViewCount = 0;

	EnemyViewMatDynamic->SetScalarParameterValue(FName("Scale"), 1000.f / MapSize);
	for (int i = 0; i < EnemyViewPos.Num(); ++i, ++ViewCount) {
		FString PosName = FString("Position_") + FString::FromInt(i + 1);
		FString AngleName = FString("Angle_") + FString::FromInt(i + 1);

		if (!EnemyViewLock[i]) {
			EnemyViewMatDynamic->SetVectorParameterValue(FName(*PosName), FLinearColor((EnemyViewPos[i].X - 20.f) / 280.f, (EnemyViewPos[i].Y - 20.f) / 280.f, 0.f, 0.f));
			EnemyViewMatDynamic->SetScalarParameterValue(FName(*AngleName), EnemyViewRotate[i]);
		}
		else
		{
			EnemyViewMatDynamic->SetVectorParameterValue(FName(*PosName), FLinearColor(0.f, 0.f, 0.f, 0.f));
			EnemyViewMatDynamic->SetScalarParameterValue(FName(*AngleName), 0.f);
		}
	}

	for (ViewCount += 1; ViewCount < 11; ++ViewCount) {
		FString PosName = FString("Position_") + FString::FromInt(ViewCount);
		FString AngleName = FString("Angle_") + FString::FromInt(ViewCount);
		EnemyViewMatDynamic->SetVectorParameterValue(FName(*PosName), FLinearColor(0.f, 0.f, 0.f, 0.f));
		EnemyViewMatDynamic->SetScalarParameterValue(FName(*AngleName), 0.f);
	}
}
