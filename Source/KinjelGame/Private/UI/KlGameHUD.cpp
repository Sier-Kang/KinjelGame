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
#include "KlPlayerController.h"
#include "Widgets/SKlPointerWidget.h"
#include "Widgets/SKlPlayerStateWidget.h"
#include "Widgets/Package/SKlPackageWidget.h"
#include "Widgets/SKlMiniMapWidget.h"
#include "Widgets/SKlGameMenuWidget.h"

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

	// Shortcut panel
	GameHUDWidget->ShotcutWidget->RegisterShotcutContainer.BindUObject(GM->KlPlayerState, 
		&AKlPlayerState::RegisterShotcunContainer);

	// Ray cast object
	GameHUDWidget->RayInfoWidget->RegisterRayInfoEvent.BindUObject(GM->KlPlayerState,
		&AKlPlayerState::RegisterRayInfoEvent);

	// Pointer insight delegate
	GM->KlPC->UpdatePointer.BindRaw(GameHUDWidget->PointerWidget.Get(), &SKlPointerWidget::UpdatePointer);

	(Cast<AKlPlayerState>(GM->KlPC->PlayerState))->UpdateStateWidget.BindRaw(GameHUDWidget->PlayerStateWidget.Get(), &SKlPlayerStateWidget::UpdateStateWidget);

	GM->KlPC->ShowGameUI.BindRaw(GameHUDWidget.Get(), &SKlGameHUDWidget::ShowGameUI);

	// Initialize Package Manager to Package Widget
	GM->InitPackageManager.BindRaw(GameHUDWidget->PackageWidget.Get(), &SKlPackageWidget::InitPackageManager);

	// Bind register mini map delegate
	GM->RegisterMiniMap.BindRaw(GameHUDWidget->MiniMapWidget.Get(), &SKlMiniMapWidget::RegisterMiniMap);

	// Bind update map data delegate
	GM->UpdateMapData.BindRaw(GameHUDWidget->MiniMapWidget.Get(), &SKlMiniMapWidget::UpdateMapData);

	// Bind save game delegate
	GameHUDWidget->GameMenuWidget->SaveGameDele.BindUObject(GM, &AKlGameMode::SaveGame);
}
