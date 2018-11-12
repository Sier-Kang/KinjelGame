// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Data/FKlTypes.h"

#include "KlPlayerCharacter.generated.h"

UCLASS()
class KINJELGAME_API AKlPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AKlPlayerCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Change character's view */
	void ChangeView(EGameViewMode::Type NewCharacterView);

	/**
	* Change current hand object 
	*/
	void ChangeHandObject(TSubclassOf<AActor> HandObjectClass);

	/**
	* Change hand object collision
	*/
	void ChangeHandObjectDetection(bool IsOpen);

	/**
	* Render hand object or not
	*/
	void RenderHandObject(bool bIsRender);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	/**
	 * Camera Spring
	 */
	UPROPERTY(VisibleAnywhere, Category = "Kinjel")
	class USpringArmComponent* CameraBoom;

	/**
	* Third person's Camera 
	*/
	UPROPERTY(VisibleAnywhere, Category = "Kinjel")
	class UCameraComponent* ThirdCamera;

	/**
	* Camera Spring
	*/
	UPROPERTY(VisibleAnywhere, Category = "Kinjel")
	UCameraComponent* FirstCamera;

	/** Character view mode */
	EGameViewMode::Type CharacterViewMode;

	/** Character's upper body status */
	EUpperBody::Type UpperBodyMode;

	/** Whether allow to switch view mode */
	bool bAllowedSwitchViewMode;

	/** Input locked flag */
	bool IsInputLocked;
private:
	/**
	* Character's action
	*/
	void MoveForward(float Value);

	void MoveRight(float Value);

	void LookUpAtRate(float Value);

	void Turn(float Value);

	void TurnAtRate(float Value);

	void OnStartJump();

	void OnStopJump();

	void OnStartRun();

	void OnStopRun();

private:
	/**
	 * First person skeletal mesh.
	 */
	UPROPERTY(VisibleDefaultsOnly, Category = "Kinjel")
	class USkeletalMeshComponent* MeshFirst;

	/**
	 *Object in hand
	 */
	UPROPERTY(VisibleAnywhere, Category = "Kinjel")
	class UChildActorComponent* HandObject;

	// Rotate rate
	float BaseLookUpRate;

	float BaseTurnRate;
};
