// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KlPickupObject.generated.h"

UCLASS()
class KINJELGAME_API AKlPickupObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKlPickupObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Pickup object ID
	int ObjectIndex;

	/** 
	* Get Pickup object's name 
	*/
	FText GetInfoText() const;

	/**
	* Picked up, return its ID
	*/
	int TakePickup();

protected:
	// Root component
	USceneComponent * RootScene;

	// Static mesh
	UStaticMeshComponent* BaseMesh;

	// Resource address, used to brush resource in random.
	TArray<FString> ResourcePath;
};
