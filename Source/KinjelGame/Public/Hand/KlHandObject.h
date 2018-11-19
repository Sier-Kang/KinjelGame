// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KlHandObject.generated.h"

UCLASS()
class KINJELGAME_API AKlHandObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKlHandObject();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/**
	* Generate object according to its id
	*/
	static TSubclassOf<AActor> SpawnHandObject(int ObjectID);

	/**
	* Change overlap detection open/close
	*/
	void ChangeOverlayDetect(bool IsOpen);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnOverlayBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* 
		OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnOverlayEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent*
		OtherComp, int32 OtherBodyIndex);

public:
	/**
	* Object index
	*/
	int ObjectIndex;

protected:
	/**
	 * Root Component
	 */
	UPROPERTY(EditAnywhere, Category = "Kinjel")
	class USceneComponent* RootScene;

	/**
	 * Object
	 */
	UPROPERTY(EditAnywhere, Category = "Kinjel")
	class UStaticMeshComponent* BaseMesh;

	/**
	 * Object collision
	 */
	UPROPERTY(EditAnywhere, Category = "Kinjel")
	class UBoxComponent* AffectCollision;

	/**Sound when hti something */
	class USoundWave* OverlaySound;
};
