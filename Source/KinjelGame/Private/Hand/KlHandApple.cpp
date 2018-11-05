// Fill out your copyright notice in the Description page of Project Settings.

#include "KlHandApple.h"
#include "ConstructorHelpers.h"
#include "Engine/StaticMesh.h"
#include "Components/BoxComponent.h"


AKlHandApple::AKlHandApple()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticBaseMesh(
		TEXT("StaticMesh'/Game/Res/PolygonAdventure/Meshes/SM_Item_Fruit_02.SM_Item_Fruit_02'")
	);

	BaseMesh->SetStaticMesh(StaticBaseMesh.Object);

	BaseMesh->SetRelativeLocation(FVector(-8.f, -3.f, 7.f));
	BaseMesh->SetRelativeRotation(FRotator(-90.f, 0.f, 0.f));
	BaseMesh->SetRelativeScale3D(FVector(1.f, 1.f, 1.f));

	AffectCollision->SetBoxExtent(FVector(10.f, 10.f, 10.f));
	AffectCollision->SetRelativeLocation(FVector(0.f, 0.f, 10.f));
}

void AKlHandApple::BeginPlay()
{
	Super::BeginPlay();

	// Define object index
	ObjectIndex = 3;
}
