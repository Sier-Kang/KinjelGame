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
#include "KlSaveGame.h"
#include "KlResourceRock.h"
#include "KlResourceTree.h"
#include "KlPickupStone.h"
#include "KlPickupWood.h"

AKlGameMode::AKlGameMode()
{
	PrimaryActorTick.bCanEverTick = true;

	bInitPackageMgr = false;

	IsCreateMiniMap = false;

	IsNeedLoadRecord = false;

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

	// Add record for the package 
	LoadRecordPackage();

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

void AKlGameMode::SaveGame()
{
	if (FKlDataHandle::Get()->RecordName.Equals(FString("Default"))) return;

	UKlSaveGame* NewRecord = Cast<UKlSaveGame>(UGameplayStatics::CreateSaveGameObject(UKlSaveGame::StaticClass()));

	NewRecord->PlayerLocation = KlPlayerCharacter->GetActorLocation();
	KlPlayerState->SaveState(NewRecord->PlayerHP, NewRecord->PlayerHunger);

	for (TActorIterator<AKlEnemyCharacter> EnemyIt(GetWorld()); EnemyIt; ++EnemyIt)
	{
		NewRecord->EnemyLoaction.Add((*EnemyIt)->GetActorLocation());
		NewRecord->EnemyHP.Add((*EnemyIt)->GetHP());
	}

	for (TActorIterator<AKlResourceRock> RockIt(GetWorld()); RockIt; ++RockIt)
	{
		NewRecord->ResourceRock.Add((*RockIt)->GetActorLocation());
	}

	for (TActorIterator<AKlResourceTree> TreeIt(GetWorld()); TreeIt; ++TreeIt) {
		NewRecord->ResourceTree.Add((*TreeIt)->GetActorLocation());
	}

	for (TActorIterator<AKlPickupStone> StoneIt(GetWorld()); StoneIt; ++StoneIt) {
		NewRecord->PickupStone.Add((*StoneIt)->GetActorLocation());
	}

	for (TActorIterator<AKlPickupWood> WoodIt(GetWorld()); WoodIt; ++WoodIt) {
		NewRecord->PickupWood.Add((*WoodIt)->GetActorLocation());
	}

	KlPackageManager::Get()->SaveData(
		NewRecord->InputIndex, 
		NewRecord->InputNum, 
		NewRecord->NormalIndex, 
		NewRecord->NormalNum,
		NewRecord->ShortcutIndex, 
		NewRecord->ShortcutNum
	);

	if (UGameplayStatics::DoesSaveGameExist(FKlDataHandle::Get()->RecordName, 0)) 
	{
		UGameplayStatics::DeleteGameInSlot(FKlDataHandle::Get()->RecordName, 0);
	}

	UGameplayStatics::SaveGameToSlot(NewRecord, FKlDataHandle::Get()->RecordName, 0);

	bool IsRecordExist = false;
	for (TArray<FString>::TIterator It(FKlDataHandle::Get()->RecordDataList); It; ++It)
	{
		if ((*It).Equals(FKlDataHandle::Get()->RecordName)) {
			IsRecordExist = true;
			break;
		}
	}

	if (!IsRecordExist) 
		FKlDataHandle::Get()->AddNewRecord();
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

void AKlGameMode::LoadRecord()
{
	if (FKlDataHandle::Get()->RecordName.IsEmpty() || FKlDataHandle::Get()->RecordName.Equals(FString("Default"))) 
		return;

	for (TArray<FString>::TIterator It(FKlDataHandle::Get()->RecordDataList); It; ++It) 
	{
		if ((*It).Equals(FKlDataHandle::Get()->RecordName)) {
			IsNeedLoadRecord = true;

			break;
		}
	}

	if (IsNeedLoadRecord && UGameplayStatics::DoesSaveGameExist(FKlDataHandle::Get()->RecordName, 0))
	{
		GameRecord = Cast<UKlSaveGame>(UGameplayStatics::LoadGameFromSlot(FKlDataHandle::Get()->RecordName, 0));
	}
	else 
	{
		IsNeedLoadRecord = false;
	}

	if (IsNeedLoadRecord && GameRecord)
	{
		KlPlayerCharacter->SetActorLocation(GameRecord->PlayerLocation);
		KlPlayerState->LoadState(GameRecord->PlayerHP, GameRecord->PlayerHunger);

		// Enemy
		int EnemyCount = 0;
		for (TActorIterator<AKlEnemyCharacter> EnemyIt(GetWorld()); EnemyIt; ++EnemyIt) 
		{
			if (EnemyCount < GameRecord->EnemyLoaction.Num())
			{
				(*EnemyIt)->SetActorLocation(GameRecord->EnemyLoaction[EnemyCount]);
				(*EnemyIt)->LoadHP(GameRecord->EnemyHP[EnemyCount]);
			}
			else 
			{
				(*EnemyIt)->IsDestroyNextTick = true;
			}

			++EnemyCount;
		}


		// Rock - pick up
		int RockCount = 0;
		for (TActorIterator<AKlResourceRock> RockIt(GetWorld()); RockIt; ++RockIt) 
		{
			if (RockCount < GameRecord->ResourceRock.Num()) {
				(*RockIt)->SetActorLocation(GameRecord->ResourceRock[RockCount]);
			}
			else 
			{
				(*RockIt)->IsDestroyNextTick = true;
			}

			++RockCount;
		}

		// Tree - pick up
		int TreeCount = 0;
		for (TActorIterator<AKlResourceTree> TreeIt(GetWorld()); TreeIt; ++TreeIt) {
			if (TreeCount < GameRecord->ResourceTree.Num()) 
			{
				(*TreeIt)->SetActorLocation(GameRecord->ResourceTree[TreeCount]);
			}
			else 
			{
				(*TreeIt)->IsDestroyNextTick = true;
			}

			++TreeCount;
		}

		// Stone - pick up
		int StoneCount = 0;
		for (TActorIterator<AKlPickupStone> StoneIt(GetWorld()); StoneIt; ++StoneIt)
		{
			if (StoneCount < GameRecord->PickupStone.Num()) 
			{
				(*StoneIt)->SetActorLocation(GameRecord->PickupStone[StoneCount]);
			}
			else
			{

				(*StoneIt)->IsDestroyNextTick = true;
			}

			++StoneCount;
		}

		// Wood - pick up 
		int WoodCount = 0;
		for (TActorIterator<AKlPickupWood> WoodIt(GetWorld()); WoodIt; ++WoodIt) 
		{
			if (WoodCount < GameRecord->PickupWood.Num()) 
			{
				(*WoodIt)->SetActorLocation(GameRecord->PickupWood[WoodCount]);
			}
			else 
			{
				(*WoodIt)->IsDestroyNextTick = true;
			}

			++WoodCount;
		}

	}
}

void AKlGameMode::LoadRecordPackage()
{
	if (!bInitPackageMgr || !IsNeedLoadRecord) return;

	if (IsNeedLoadRecord && GameRecord)
	{
		KlPackageManager::Get()->LoadRecord(
			&GameRecord->InputIndex, 
			&GameRecord->InputNum, 
			&GameRecord->NormalIndex, 
			&GameRecord->NormalNum, 
			&GameRecord->ShortcutIndex, 
			&GameRecord->ShortcutNum
		);
	}

	IsNeedLoadRecord = false;
}
