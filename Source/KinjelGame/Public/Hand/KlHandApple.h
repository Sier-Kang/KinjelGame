// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Hand/KlHandObject.h"
#include "KlHandApple.generated.h"

/**
 * 
 */
UCLASS()
class KINJELGAME_API AKlHandApple : public AKlHandObject
{
	GENERATED_BODY()
	
public:
	AKlHandApple();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
