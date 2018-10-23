// Fill out your copyright notice in the Description page of Project Settings.

#include "KlMenuController.h"


AKlMenuController::AKlMenuController() 
{
	// Show mouse cursor in menu system
	bShowMouseCursor = true;
}

void AKlMenuController::BeginPlay()
{
	// Set default input mode in menu
	FInputModeUIOnly InputData;
	InputData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	// InputData.SetWidgetToFocus();
	SetInputMode(InputData);
}
