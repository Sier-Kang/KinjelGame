// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Hand/KlHandObject.h"
#include "KlHandHammer.generated.h"

/**
 * 
 */
UCLASS()
class KINJELGAME_API AKlHandHammer : public AKlHandObject
{
	GENERATED_BODY()
	
public:
	AKlHandHammer();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	class UStaticMeshComponent* ExtendMesh;
};
