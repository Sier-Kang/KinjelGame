// Fill out your copyright notice in the Description page of Project Settings.

#include "KinjelGame.h"
#include "Modules/ModuleManager.h"
#include "UI/Style/KlStyle.h"

void FKlGameModule::StartupModule() 
{
	// Initialize the style
	FSlateStyleRegistry::UnRegisterSlateStyle(KlStyle::GetStyleSetName());
	KlStyle::Initialize();
}

void FKlGameModule::ShutdownModule() 
{
	KlStyle::ShutDown();
}

IMPLEMENT_PRIMARY_GAME_MODULE(FKlGameModule, KinjelGame, "KinjelGame");