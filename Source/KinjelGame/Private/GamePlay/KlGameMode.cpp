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

AKlGameMode::AKlGameMode()
{
	PrimaryActorTick.bCanEverTick = true;

	bInitPackageMgr = false;

	// Set defaut class
	HUDClass = AKlGameHUD::StaticClass();
	PlayerControllerClass = AKlPlayerController::StaticClass();
	PlayerStateClass = AKlPlayerState::StaticClass();
	DefaultPawnClass = AKlPlayerCharacter::StaticClass();
}

void AKlGameMode::Tick(float DeltaSeconds)
{
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
