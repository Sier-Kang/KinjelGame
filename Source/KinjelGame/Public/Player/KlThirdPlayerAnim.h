// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/KlPlayerAnim.h"
#include "KlThirdPlayerAnim.generated.h"

/**
 * 
 */
UCLASS()
class KINJELGAME_API UKlThirdPlayerAnim : public UKlPlayerAnim
{
	GENERATED_BODY()
	
public:
	UKlThirdPlayerAnim();

public:
	/**
	* Is character in air
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayAnim")
	bool bInAir;

	/**
	* character's direction
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayAnim")
	float Direction;
};
