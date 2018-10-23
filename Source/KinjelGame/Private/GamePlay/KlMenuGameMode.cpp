// Fill out your copyright notice in the Description page of Project Settings.

#include "KlMenuGameMode.h"
#include "KlMenuController.h"
#include "KlMenuHUD.h"

AKlMenuGameMode::AKlMenuGameMode()
{
	// Set default properties in menu game mode.
	PlayerControllerClass = AKlMenuController::StaticClass();
	HUDClass = AKlMenuHUD::StaticClass();
}
