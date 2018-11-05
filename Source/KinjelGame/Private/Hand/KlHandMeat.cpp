// Fill out your copyright notice in the Description page of Project Settings.

#include "KlHandMeat.h"
#include "ConstructorHelpers.h"
#include "Engine/StaticMesh.h"
#include "Components/BoxComponent.h"

AKlHandMeat::AKlHandMeat()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticBaseMesh(
		TEXT("StaticMesh'/Game/Res/PolygonAdventure/Meshes/SM_Prop_Meat_02.SM_Prop_Meat_02'")
	);

	BaseMesh->SetStaticMesh(StaticBaseMesh.Object);

	BaseMesh->SetRelativeLocation(FVector(6.f, -7.044f, 2.62f));
	BaseMesh->SetRelativeRotation(FRotator(-50.f, 90.f, 0.f));
	BaseMesh->SetRelativeScale3D(FVector(0.75f, 0.75f, 0.75f));

	AffectCollision->SetBoxExtent(FVector(10.f, 10.f, 10.f));
	AffectCollision->SetRelativeLocation(FVector(0.f, 0.f, 10.f));
}

void AKlHandMeat::BeginPlay()
{
	Super::BeginPlay();

	// Define object index
	ObjectIndex = 4;
}
