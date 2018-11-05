// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Hand/KlHandObject.h"
#include "KlHandMeat.generated.h"

/**
 * 
 */
UCLASS()
class KINJELGAME_API AKlHandMeat : public AKlHandObject
{
	GENERATED_BODY()
	
public:
	AKlHandMeat();

protected:
	virtual void BeginPlay() override;
};
