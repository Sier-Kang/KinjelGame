// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Hand/KlHandObject.h"
#include "KlHandAxe.generated.h"

/**
 * 
 */
UCLASS()
class KINJELGAME_API AKlHandAxe : public AKlHandObject
{
	GENERATED_BODY()
	
public:
	AKlHandAxe();

protected:
	virtual void BeginPlay() override;
};
