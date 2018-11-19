// Fill out your copyright notice in the Description page of Project Settings.

#include "KlGameMode.h"
#include "KlPlayerCharacter.h"
#include "KlPlayerController.h"
#include "KlPlayerState.h"
#include "KlGameHUD.h"
#include "FKlHelper.h"
#include "Data/FKlDataHandle.h"
#include "KlGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "KlPackageManager.h"
#include "KlSceneCapture2D.h"
#include "Player/KlPlayerController.h"
#include "Player/KlPlayerCharacter.h"
#include "KlEnemyCharacter.h"

AKlGameMode::AKlGameMode()
{
	PrimaryActorTick.bCanEverTick = true;

	bInitPackageMgr = false;

	// Set default class
	HUDClass = AKlGameHUD::StaticClass();
	PlayerControllerClass = AKlPlayerController::StaticClass();
	PlayerStateClass = AKlPlayerState::StaticClass();
	DefaultPawnClass = AKlPlayerCharacter::StaticClass();
}

void AKlGameMode::Tick(float DeltaSeconds)
{
	// Initialize mini map system and update
	InitializeMiniMapCamera();

	// Initialize package system and update 
	InitializePackage();
}

void AKlGameMode::InitGamePlayModule()
{
	if (KlPC) return;

	KlPC = Cast<AKlPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	KlPlayerState = Cast<AKlPlayerState>(KlPC->PlayerState);
	KlPlayerCharacter = Cast<AKlPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

void AKlGameMode::BeginPlay()
{
	// Initialize game data
	// FKlHelper::Debug(FString("AKlGameMode::BeginPlay runs.", 30.f));
	FKlDataHandle::Get()->InitializeGameData();

	if (!KlPC) {
		InitGamePlayModule();
	}
}

void AKlGameMode::InitializePackage()
{
	if (bInitPackageMgr) return;

	//Call PackageWidget to initialize package ui
	InitPackageManager.ExecuteIfBound();

	KlPackageManager::Get()->PlayerThrowObject.BindUObject(KlPlayerCharacter, &AKlPlayerCharacter::PlayerThrowObject);

	KlPackageManager::Get()->ChangeHandObject.BindUObject(KlPlayerState, &AKlPlayerState::ChangeHandObject);

	bInitPackageMgr = true;
}

void AKlGameMode::InitializeMiniMapCamera()
{
	if (!IsCreateMiniMap && GetWorld())
	{
		MiniMapCamera = GetWorld()->SpawnActor<AKlSceneCapture2D>(AKlSceneCapture2D::StaticClass());

		RegisterMiniMap.ExecuteIfBound(MiniMapCamera->GetMiniMapTex());

		KlPC->UpdateMiniMapWidth.BindUObject(MiniMapCamera, &AKlSceneCapture2D::UpdateMiniMapWidth);

		IsCreateMiniMap = true;
	}


	if (IsCreateMiniMap)
	{
		MiniMapCamera->UpdateTransform(KlPlayerCharacter->GetActorLocation(), KlPlayerCharacter->GetActorRotation());

		TArray<FVector2D> EnemyPosList;
		TArray<bool> EnemyLockList;
		TArray<float> EnemyRotateList;

		for (TActorIterator<AKlEnemyCharacter> EnemyIt(GetWorld()); EnemyIt; ++EnemyIt)
		{
			FVector EnemyPos = FVector((*EnemyIt)->GetActorLocation().X - KlPlayerCharacter->GetActorLocation().X, (*EnemyIt)->GetActorLocation().Y - KlPlayerCharacter->GetActorLocation().Y, 0.f);
			EnemyPos = FQuat(FVector::UpVector, FMath::DegreesToRadians(-KlPlayerCharacter->GetActorRotation().Yaw - 90.f)) * EnemyPos;
			EnemyPosList.Add(FVector2D(EnemyPos.X, EnemyPos.Y));

			EnemyLockList.Add((*EnemyIt)->IsLockPlayer());
			EnemyRotateList.Add((*EnemyIt)->GetActorRotation().Yaw - KlPlayerCharacter->GetActorRotation().Yaw);
		}

		UpdateMapData.ExecuteIfBound(KlPlayerCharacter->GetActorRotation(), MiniMapCamera->GetMapSize(), &EnemyPosList, &EnemyLockList, &EnemyRotateList);
	}
}
