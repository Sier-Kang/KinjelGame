// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Data/FKlTypes.h"
#include "KlPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class KINJELGAME_API AKlPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	/**
	* Constructor
	*/
	AKlPlayerController();

	/**
	* Tick
	*/
	virtual void Tick(float DeltaSeconds) override;

	/**
	* Input Action/Axis
	*/
	virtual void SetupInputComponent() override;

public:
	class AKlPlayerCharacter* PlayerCharacter;

protected:
	/**
	* Begin play
	*/
	virtual void BeginPlay() override;

private:
	/** Change view */
	void ChangeView();

	/** Mouse press&release events.*/
	void LeftEventStart();

	void LeftEventStop();

	void RightEventStart();

	void RightEventStop();

private:
	/** Left pre action */
	EUpperBody::Type LeftUpperType;

	/** Right pre action */
	EUpperBody::Type RightUpperType;
};
