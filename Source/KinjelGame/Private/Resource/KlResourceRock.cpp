// Fill out your copyright notice in the Description page of Project Settings.

#include "KlResourceRock.h"
#include "RandomStream.h"
#include "ConstructorHelpers.h"
#include "Engine/StaticMesh.h"
#include "Components/StaticMeshComponent.h"

AKlResourceRock::AKlResourceRock()
{
	ResourcePath.Add(FString("StaticMesh'/Game/Res/PolygonAdventure/Meshes/SM_Env_Rock_02.SM_Env_Rock_02'"));
	ResourcePath.Add(FString("StaticMesh'/Game/Res/PolygonAdventure/Meshes/SM_Env_Rock_03.SM_Env_Rock_03'"));
	ResourcePath.Add(FString("StaticMesh'/Game/Res/PolygonAdventure/Meshes/SM_Env_Rock_03_Snow.SM_Env_Rock_03_Snow'"));
	ResourcePath.Add(FString("StaticMesh'/Game/Res/PolygonAdventure/Meshes/SM_Env_Rock_04.SM_Env_Rock_04'"));
	ResourcePath.Add(FString("StaticMesh'/Game/Res/PolygonAdventure/Meshes/SM_Env_Rock_04_Snow.SM_Env_Rock_04_Snow'"));


	FRandomStream Stream;

	// Spawn new random seed
	Stream.GenerateNewSeed();

	int RandIndex = Stream.RandRange(0, ResourcePath.Num() - 1);

	ConstructorHelpers::FObjectFinder<UStaticMesh> StaticBaseMesh(*ResourcePath[RandIndex]);
	BaseMesh->SetStaticMesh(StaticBaseMesh.Object);

	ResourceIndex = 2;
}
