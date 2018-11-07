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
}
