// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/SceneCapture2D.h"
#include "KlSceneCapture2D.generated.h"

/**
 * 
 */
UCLASS()
class KINJELGAME_API AKlSceneCapture2D : public ASceneCapture2D
{
	GENERATED_BODY()
	
public:
	AKlSceneCapture2D();

	/** Get Mini map texture */
	class UTextureRenderTarget2D* GetMiniMapTex();

	/** Update Transform */
	void UpdateTransform(FVector NormLocation, FRotator NormRotator);
	
	/** Update view */
	void UpdateMiniMapWidth(int Delta);

	/** Get Mini map size */
	float GetMapSize();

private:
	UTextureRenderTarget2D * MiniMapTex;
};
