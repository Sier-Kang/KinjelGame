// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Data/FKlTypes.h"

#include "KlResourceObject.generated.h"


UCLASS()
class KINJELGAME_API AKlResourceObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKlResourceObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/**
	* Generate flob object when resource object's hp is 0
	*/
	void CreateFlobObject();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Resource ID
	int ResourceIndex;

	/**
	* Get Pickup object's name
	*/
	FText GetInfoText() const;

	/**
	* Get resource type
	*/
	EResourceType::Type GetResourceType() const;

	/**
	* Get HP in percent
	*/
	float GetHPRange() const;

	/**
	* Get damage
	*/
	AKlResourceObject* TakeObjectDamage(int Damage);

protected:
	// Root component
	USceneComponent * RootScene;

	// Static mesh
	UStaticMeshComponent* BaseMesh;

	// Resource address, used to brush resource in random.
	TArray<FString> ResourcePath;

	/** Health component */
	int HP;

	int BaseHP;
};
