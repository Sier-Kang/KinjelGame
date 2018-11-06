// Fill out your copyright notice in the Description page of Project Settings.

#include "KlGameHUD.h"
#include "Widgets/SKlGameHUDWidget.h"
#include "SWeakWidget.h"
#include "KlGameMode.h"
#include "Widgets/SKlShotcutWidget.h"
#include "Kismet/GameplayStatics.h"
#include "KlPlayerState.h"
#include "Engine/Engine.h"
#include "Engine/GameViewportClient.h"
#include "Widgets/SKlRayInfoWidget.h"

AKlGameHUD::AKlGameHUD()
{
	if (GEngine && GEngine->GameViewport) {
		SAssignNew(GameHUDWidget, SKlGameHUDWidget);
		GEngine->GameViewport->AddViewportWidgetContent(
			SNew(SWeakWidget)
			.PossiblyNullContent(GameHUDWidget.ToSharedRef())
		);
	}
}

void AKlGameHUD::BeginPlay()
{
	Super::BeginPlay();

	GM = Cast<AKlGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (!GM) return;

	GM->InitGamePlayModule();

	GameHUDWidget->ShotcutWidget->RegisterShotcutContainer.BindUObject(GM->KlPlayerState, 
		&AKlPlayerState::RegisterShotcunContainer);

	GameHUDWidget->RayInfoWidget->RegisterRayInfoEvent.BindUObject(GM->KlPlayerState,
		&AKlPlayerState::RegisterRayInfoEvent);
}
