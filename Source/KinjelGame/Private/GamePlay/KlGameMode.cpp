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

AKlGameMode::AKlGameMode()
{
	PrimaryActorTick.bCanEverTick = true;

	// Set defaut class
	HUDClass = AKlGameHUD::StaticClass();
	PlayerControllerClass = AKlPlayerController::StaticClass();
	PlayerStateClass = AKlPlayerState::StaticClass();
	DefaultPawnClass = AKlPlayerCharacter::StaticClass();
}

void AKlGameMode::Tick(float DeltaSeconds)
{
	
}

void AKlGameMode::BeginPlay()
{
	FKlHelper::Debug(FString("DataHandle: ") + FKlDataHandle::Get()->RecordName, 30.f);

	Cast<UKlGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->GameName;
}
