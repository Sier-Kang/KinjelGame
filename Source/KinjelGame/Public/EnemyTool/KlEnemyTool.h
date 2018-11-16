// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KlEnemyTool.generated.h"

UCLASS()
class KINJELGAME_API AKlEnemyTool : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKlEnemyTool();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/**
	* Allowed detection
	*/
	void ChangeOverlapDetect(bool IsOpen);

	static TSubclassOf<AActor> SpawnEnemyWeapon();

	static TSubclassOf<AActor> SpawnEnemyShield();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	UFUNCTION()
	virtual void OnOverlayBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
	UFUNCTION()
	virtual void OnOverlayEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	/** Root Component */
	USceneComponent * RootScene;

	/** Static Mesh */
	UPROPERTY(EditAnywhere, Category = "Mesh")
	UStaticMeshComponent* BaseMesh;

	/** Box collision */
	UPROPERTY(EditAnywhere, Category = "Mesh")
	class UBoxComponent* AffectCollision;
};
