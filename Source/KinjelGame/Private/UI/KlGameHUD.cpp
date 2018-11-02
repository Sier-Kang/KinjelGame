// Fill out your copyright notice in the Description page of Project Settings.

#include "KlGameHUD.h"
#include "Widgets/SKlGameHUDWidget.h"
#include "SWeakWidget.h"

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
