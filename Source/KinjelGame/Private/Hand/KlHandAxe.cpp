// Fill out your copyright notice in the Description page of Project Settings.

#include "KlHandAxe.h"
#include "ConstructorHelpers.h"
#include "Engine/StaticMesh.h"
#include "Components/BoxComponent.h"

AKlHandAxe::AKlHandAxe()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticBaseMesh(
		TEXT("StaticMesh'/Game/Res/PolygonAdventure/Meshes/SM_Wep_Axe_01.SM_Wep_Axe_01'")
	);

	BaseMesh->SetStaticMesh(StaticBaseMesh.Object);

	BaseMesh->SetRelativeLocation(FVector(-28.0f, -4.9f, 3.23f));
	BaseMesh->SetRelativeRotation(FRotator(0.f, -90.f, 90.f));
	BaseMesh->SetRelativeScale3D(FVector(1.f, 1.f, 1.f));

	// Set collision property
	AffectCollision->SetRelativeLocation(FVector(32.f, -5.f, 3.f));
	AffectCollision->SetRelativeScale3D(FVector(0.37f, 0.5f, 0.125f));
}

void AKlHandAxe::BeginPlay()
{
	Super::BeginPlay();

	// Define Object index
	ObjectIndex = 5;
}
