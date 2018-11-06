// Fill out your copyright notice in the Description page of Project Settings.

#include "KlPickupWood.h"
#include "ConstructorHelpers.h"
#include "Engine/StaticMesh.h"
#include "Components/StaticMeshComponent.h"

AKlPickupWood::AKlPickupWood()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticBaseMesh(
		TEXT("StaticMesh'/Game/Res/PolygonAdventure/Meshes/SM_Prop_Loghalf_01.SM_Prop_Loghalf_01'")
	);
	BaseMesh->SetStaticMesh(StaticBaseMesh.Object);

	BaseMesh->SetRelativeScale3D(FVector(0.4f));

	ObjectIndex = 1;
}
