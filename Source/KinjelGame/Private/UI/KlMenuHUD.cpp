// Fill out your copyright notice in the Description page of Project Settings.

#include "KlMenuHUD.h"
#include "Widgets/SKlMenuHUDWidget.h"
#include "SlateBasics.h"


AKlMenuHUD::AKlMenuHUD() 
{
	if (GEngine && GEngine->GameViewport)
	{
		SAssignNew(MenuHUDWidget, SKlMenuHUDWidget);
		GEngine->GameViewport->AddViewportWidgetContent(
			SNew(SWeakWidget).PossiblyNullContent(MenuHUDWidget.ToSharedRef())
		);
	}
}
