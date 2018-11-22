// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "KlSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class KINJELGAME_API UKlSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, Category = "Kinjel")
	FVector PlayerLocation;

	UPROPERTY(VisibleAnywhere, Category = "Kinjel")
	float PlayerHP;

	UPROPERTY(VisibleAnywhere, Category = "Kinjel")
	float PlayerHunger;

	UPROPERTY(VisibleAnywhere, Category = "Kinjel")
	TArray<int32> InputIndex;

	UPROPERTY(VisibleAnywhere, Category = "Kinjel")
	TArray<int32> InputNum;

	UPROPERTY(VisibleAnywhere, Category = "Kinjel")
	TArray<int32> NormalIndex;

	UPROPERTY(VisibleAnywhere, Category = "Kinjel")
	TArray<int32> NormalNum;

	UPROPERTY(VisibleAnywhere, Category = "Kinjel")
	TArray<int32> ShortcutIndex;

	UPROPERTY(VisibleAnywhere, Category = "Kinjel")
	TArray<int32> ShortcutNum;

	UPROPERTY(VisibleAnywhere, Category = "Kinjel")
	TArray<FVector> EnemyLoaction;

	UPROPERTY(VisibleAnywhere, Category = "Kinjel")
	TArray<float> EnemyHP;

	UPROPERTY(VisibleAnywhere, Category = "Kinjel")
	TArray<FVector> ResourceRock;

	UPROPERTY(VisibleAnywhere, Category = "Kinjel")
	TArray<FVector> ResourceTree;

	UPROPERTY(VisibleAnywhere, Category = "Kinjel")
	TArray<FVector> PickupStone;

	UPROPERTY(VisibleAnywhere, Category = "Kinjel")
	TArray<FVector> PickupWood;
};
