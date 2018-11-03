// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "KlGameHUD.generated.h"

/**
 * 
 */
UCLASS()
class KINJELGAME_API AKlGameHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	AKlGameHUD();

public:
	/** Game Mode interface */
	class AKlGameMode* GM;

protected:
	virtual void BeginPlay() override;

protected:
	TSharedPtr<class SKlGameHUDWidget> GameHUDWidget;
};
