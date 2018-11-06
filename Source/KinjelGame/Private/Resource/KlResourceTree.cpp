// Fill out your copyright notice in the Description page of Project Settings.

#include "KlResourceTree.h"
#include "RandomStream.h"
#include "ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"

AKlResourceTree::AKlResourceTree()
{
	ResourcePath.Add(FString("StaticMesh'/Game/Res/PolygonAdventure/Meshes/SM_Env_Tree_07.SM_Env_Tree_07'"));
	ResourcePath.Add(FString("StaticMesh'/Game/Res/PolygonAdventure/Meshes/SM_Env_Tree_016.SM_Env_Tree_016'"));
	ResourcePath.Add(FString("StaticMesh'/Game/Res/PolygonAdventure/Meshes/SM_Env_Tree_014_Snow.SM_Env_Tree_014_Snow'"));
	ResourcePath.Add(FString("StaticMesh'/Game/Res/PolygonAdventure/Meshes/SM_Env_Tree_012.SM_Env_Tree_012'"));
	ResourcePath.Add(FString("StaticMesh'/Game/Res/PolygonAdventure/Meshes/SM_Env_TreePine_01_Snow.SM_Env_TreePine_01_Snow'"));
	ResourcePath.Add(FString("StaticMesh'/Game/Res/PolygonAdventure/Meshes/SM_Env_Tree_01_Snow.SM_Env_Tree_01_Snow'"));
	ResourcePath.Add(FString("StaticMesh'/Game/Res/PolygonAdventure/Meshes/SM_Env_Tree_06_Snow.SM_Env_Tree_06_Snow'"));
	ResourcePath.Add(FString("StaticMesh'/Game/Res/PolygonAdventure/Meshes/SM_Env_TreeDead_02_Snow.SM_Env_TreeDead_02_Snow'"));
	ResourcePath.Add(FString("StaticMesh'/Game/Res/PolygonAdventure/Meshes/SM_Env_TreeDead_01.SM_Env_TreeDead_01'"));
	ResourcePath.Add(FString("StaticMesh'/Game/Res/PolygonAdventure/Meshes/SM_Env_Tree_012_Snow.SM_Env_Tree_012_Snow'"));

	// Spawn random seed
	FRandomStream Stream;

	Stream.GenerateNewSeed();

	int RandIndex = Stream.RandRange(0, ResourcePath.Num()-1);

	ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMesh(*ResourcePath[RandIndex]);

	BaseMesh->SetStaticMesh(StaticMesh.Object);

	ResourceIndex = 1;
}
