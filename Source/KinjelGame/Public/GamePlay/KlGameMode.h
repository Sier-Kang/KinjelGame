// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "KlGameMode.generated.h"

/**
* Initialize Package Manager Delegate
*/
DECLARE_DELEGATE(FInitPackageManager)

/** Register Mini map's texture and material*/
DECLARE_DELEGATE_OneParam(FRegisterMiniMap, class UTextureRenderTarget2D*)

/** Update Mini map's data */
DECLARE_DELEGATE_FiveParams(FUpdateMapData, const FRotator, const float, const TArray<FVector2D>*, const TArray<bool>*, const TArray<float>*)

/**
 * 
 */
UCLASS()
class KINJELGAME_API AKlGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AKlGameMode();

	virtual void Tick(float DeltaSeconds) override;

	/**
	* Use to invoked by HUD
	*/
	void InitGamePlayModule();

public:
	class AKlPlayerController* KlPC;

	class AKlPlayerState* KlPlayerState;

	class AKlPlayerCharacter* KlPlayerCharacter;

	FInitPackageManager InitPackageManager;

	FRegisterMiniMap RegisterMiniMap;

	FUpdateMapData UpdateMapData;

protected:
	virtual void BeginPlay() override;

	/**
	* Initialize package manager
	*/
	void InitializePackage();

	/**
	* Initialize mini map camera
	*/
	void InitializeMiniMapCamera();

private:
	bool bInitPackageMgr;

	/** Flag of weather create mini map camera and its ptr */
	bool IsCreateMiniMap;

	class AKlSceneCapture2D* MiniMapCamera;
};
