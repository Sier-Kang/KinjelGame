// Fill out your copyright notice in the Description page of Project Settings.

#include "KlPlayerController.h"
#include "Player/KlPlayerCharacter.h"

AKlPlayerController::AKlPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AKlPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (!PlayerCharacter)
	{
		PlayerCharacter = Cast<AKlPlayerCharacter>(GetCharacter());
	}

	// Set UI property etc and Input mode.
	bShowMouseCursor = false;
	FInputModeGameOnly InputMode;
	InputMode.SetConsumeCaptureMouseDown(true);
	SetInputMode(InputMode);
}

void AKlPlayerController::Tick(float DeltaSeconds)
{

}

void AKlPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Bind change view
	InputComponent->BindAction("ChangeView", IE_Pressed, this, &AKlPlayerController::ChangeView);
	InputComponent->BindAction("LeftEvent", IE_Pressed, this, &AKlPlayerController::LeftEventStart);
	InputComponent->BindAction("LeftEvent", IE_Released, this, &AKlPlayerController::LeftEventStop);
	InputComponent->BindAction("RightEvent", IE_Pressed, this, &AKlPlayerController::RightEventStart);
	InputComponent->BindAction("RightEvent", IE_Released, this, &AKlPlayerController::RightEventStop);
}

void AKlPlayerController::ChangeView()
{
	if (!PlayerCharacter)
	{
		return;
	}

	switch (PlayerCharacter->CharacterViewMode) 
	{
	case EGameViewMode::First:
		PlayerCharacter->ChangeView(EGameViewMode::Third);

		break;
	case EGameViewMode::Third:
		PlayerCharacter->ChangeView(EGameViewMode::First);

		break;
	default:

		break;
	}
}

void AKlPlayerController::LeftEventStart()
{

}

void AKlPlayerController::LeftEventStop()
{

}

void AKlPlayerController::RightEventStart()
{

}

void AKlPlayerController::RightEventStop()
{

}

