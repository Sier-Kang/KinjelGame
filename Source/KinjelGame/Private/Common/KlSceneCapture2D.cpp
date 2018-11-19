// Fill out your copyright notice in the Description page of Project Settings.

#include "KlSceneCapture2D.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/TextureRenderTarget2D.h"

AKlSceneCapture2D::AKlSceneCapture2D()
{
	GetCaptureComponent2D()->bCaptureEveryFrame = true;

	GetCaptureComponent2D()->CaptureSource = ESceneCaptureSource::SCS_SceneColorSceneDepth;

	GetCaptureComponent2D()->ProjectionType = ECameraProjectionMode::Orthographic;

	GetCaptureComponent2D()->OrthoWidth = 3000.f;

	SetActorRotation(FRotator(-90.f, 0.f, 0.f));
}

UTextureRenderTarget2D* AKlSceneCapture2D::GetMiniMapTex()
{
	MiniMapTex = NewObject<UTextureRenderTarget2D>();

	MiniMapTex->InitAutoFormat(256, 256);

	GetCaptureComponent2D()->TextureTarget = MiniMapTex;

	return MiniMapTex;
}

void AKlSceneCapture2D::UpdateTransform(FVector NormLocation, FRotator NormRotator)
{
	SetActorLocation(NormLocation + FVector(0.f, 0.f, 1000.f));

	SetActorRotation(FRotator(-90.f, NormRotator.Yaw, NormRotator.Roll));
}

void AKlSceneCapture2D::UpdateMiniMapWidth(int Delta)
{
	const float PreWidth = GetCaptureComponent2D()->OrthoWidth;

	GetCaptureComponent2D()->OrthoWidth = FMath::Clamp<float>(PreWidth + Delta, 2000.f, 4000.f);
}

float AKlSceneCapture2D::GetMapSize()
{
	return GetCaptureComponent2D()->OrthoWidth;
}
