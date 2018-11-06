// Fill out your copyright notice in the Description page of Project Settings.

#include "KlPickupStone.h"
#include "ConstructorHelpers.h"
#include "Engine/StaticMesh.h"
#include "Components/StaticMeshComponent.h"

AKlPickupStone::AKlPickupStone()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticBaseMesh(
		TEXT("StaticMesh'/Game/Res/PolygonAdventure/Meshes/SM_Prop_StoneBlock_01.SM_Prop_StoneBlock_01'")
	);
	BaseMesh->SetStaticMesh(StaticBaseMesh.Object);

	BaseMesh->SetRelativeScale3D(FVector(0.8f, 0.8f, 0.5f));

	ObjectIndex = 2;
}
