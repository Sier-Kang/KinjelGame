// Fill out your copyright notice in the Description page of Project Settings.

#include "KlHandWood.h"
#include "ConstructorHelpers.h"
#include "Engine/StaticMesh.h"
#include "Components/BoxComponent.h"

AKlHandWood::AKlHandWood()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticBaseMesh(
		TEXT("StaticMesh'/Game/Res/PolygonAdventure/Meshes/SM_Env_TreeLog_01.SM_Env_TreeLog_01'")
	);

	BaseMesh->SetStaticMesh(StaticBaseMesh.Object);

	BaseMesh->SetRelativeScale3D(FVector(0.1f, 0.1f, 0.1f));
	BaseMesh->SetRelativeRotation(FRotator(0.f, -20.f, 0.f));

	AffectCollision->SetBoxExtent(FVector(10.f, 10.f, 10.f));
	AffectCollision->SetRelativeLocation(FVector(0.f, 0.f, 10.f));
}

void AKlHandWood::BeginPlay()
{
	Super::BeginPlay();

	// Define object index
	ObjectIndex = 1;
}
