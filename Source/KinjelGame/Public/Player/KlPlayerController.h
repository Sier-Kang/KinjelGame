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

	/**
	* Change hand object of the character
	*/
	void ChangeHandObject();

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

	void ScrollUpEvent();

	void ScrollDownEvent();

	/**
	* Change pre upper body action
	*/
	void ChangePreUpperType(EUpperBody::Type RightType);

private:
	/** Left pre action */
	EUpperBody::Type LeftUpperType;

	/** Right pre action */
	EUpperBody::Type RightUpperType;

	/** Mouse left/right button down flag. */
	bool bIsLeftButtonDown;

	bool bIsRightButtonDown;
};
