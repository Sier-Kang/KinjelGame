// Fill out your copyright notice in the Description page of Project Settings.

#include "KlResourceObject.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"


// Sets default values
AKlResourceObject::AKlResourceObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	RootComponent = RootScene;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetupAttachment(RootScene);
	BaseMesh->SetCollisionProfileName(FName("ResourceProfile"));

	BaseMesh->SetGenerateOverlapEvents(true);
}

// Called when the game starts or when spawned
void AKlResourceObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKlResourceObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

