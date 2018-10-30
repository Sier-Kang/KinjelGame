// Fill out your copyright notice in the Description page of Project Settings.

#include "KlMenuGameMode.h"
#include "KlMenuController.h"
#include "KlMenuHUD.h"
#include "KlGameInstance.h"
#include "Kismet/GameplayStatics.h"

AKlMenuGameMode::AKlMenuGameMode()
{
	// Set default properties in menu game mode.
	PlayerControllerClass = AKlMenuController::StaticClass();
	HUDClass = AKlMenuHUD::StaticClass();
}

void AKlMenuGameMode::BeginPlay()
{
	Super::BeginPlay();

	Cast<UKlGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->GameName = FString("KinjelGame");
}
