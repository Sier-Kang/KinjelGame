// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
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

private:
	/**
	 * First person skeletal mesh.
	 */
	UPROPERTY(VisibleDefaultsOnly, Category = "Kinjel")
	class USkeletalMeshComponent* MeshFirst;
};
