// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyTool/KlEnemyTool.h"
#include "KlEnemyWeapon.generated.h"

/**
 * 
 */
UCLASS()
class KINJELGAME_API AKlEnemyWeapon : public AKlEnemyTool
{
	GENERATED_BODY()
	
public:
	AKlEnemyWeapon();

protected:
	virtual void OnOverlayBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) override;
};
