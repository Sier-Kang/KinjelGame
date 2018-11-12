// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Data/FKlTypes.h"
#include "KlPlayerController.generated.h"

/** Pointer insight delegate */
DECLARE_DELEGATE_TwoParams(FUpdatePointer, bool, float)

/** Switch game ui delegate */
DECLARE_DELEGATE_TwoParams(FShowGameUI, EGameUIType::Type, EGameUIType::Type)

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
	/** Player controller ptr */
	class AKlPlayerCharacter* PlayerCharacter;

	/** pointer insight */ 
	FUpdatePointer UpdatePointer;

	/** Switch game ui delegate */
	FShowGameUI ShowGameUI;

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

	/**
	* View ray cast
	*/
	FHitResult RayGetHitResult(FVector TraceStart, FVector TraceEnd);

	/**
	* Draw ray line
	*/
	void DrawRayLine(FVector StartPos, FVector EndPos, float Duration);

	/**
	* Ray cast of view
	*/
	void RunRayCast();

	/**
	* Character's state machine of its action
	*/
	void StateMachine();

	/**
	* Escape Event
	*/
	void EscEvent();

	/**
	* Package Event
	*/
	void PackageEvent();

	/**
	* ChatRoom Event
	*/
	void ChatRoomEvent();

	/**
	* Switch game mode 
	*/
	void SwitchInputMode(bool bIsGameOnly);

	/**
	* Set Input locked
	*/
	void LockedInput(bool bLockedInput);

private:
	/** Left pre action */
	EUpperBody::Type LeftUpperType;

	/** Right pre action */
	EUpperBody::Type RightUpperType;

	/** Mouse left/right button down flag. */
	bool bIsLeftButtonDown;

	bool bIsRightButtonDown;

	/** View ray cast actor */
	AActor* RayCastActor;

	/** Current Game UI Type */
	EGameUIType::Type CurrentUIType;
};
