// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "KlGameMode.generated.h"

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

protected:
	virtual void BeginPlay() override;
};
