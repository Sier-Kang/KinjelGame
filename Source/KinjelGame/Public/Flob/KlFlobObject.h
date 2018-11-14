// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KlFlobObject.generated.h"

UCLASS()
class KINJELGAME_API AKlFlobObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKlFlobObject();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/**
	* Initialize object
	*/
	void CreateFlobObject(int ObjectID);

	/**
	* Throw object
	*/
	void ThrowFlobObject(int ObjectID, float DirYaw);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void RenderTexture();

	/**
	* Detect player character timer event
	*/
	void DetectPlayer();

	/**
	* Destroy Event
	*/
	void DestroyEvent();

private:
	class UBoxComponent* BoxCollision;

	class UStaticMeshComponent* BaseMesh;

	class UTexture* ObjectIconTex;

	class UMaterialInstanceDynamic* ObjectIconMatDynamic;

	/** Object type ID */
	int ObjectIndex;

	/** Player Character */
	class AKlPlayerCharacter* PlayerCharacter;

	/** Detect Timer handle */
	FTimerHandle DetectTimer;

	/** Destroy Timer Handle */
	FTimerHandle DestroyTimer;
};
