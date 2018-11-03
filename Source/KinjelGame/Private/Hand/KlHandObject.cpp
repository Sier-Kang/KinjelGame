// Fill out your copyright notice in the Description page of Project Settings.

#include "KlHandObject.h"
#include "Components/StaticMeshComponent.h"
#include "ConstructorHelpers.h"
#include "Engine/StaticMesh.h"


// Sets default values
AKlHandObject::AKlHandObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = BaseMesh;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticBaseMesh(
		TEXT("StaticMesh'/Game/Res/PolygonAdventure/Meshes/SM_Wep_Axe_01.SM_Wep_Axe_01'")
	);

	BaseMesh->SetStaticMesh(StaticBaseMesh.Object);
}

// Called when the game starts or when spawned
void AKlHandObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKlHandObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

