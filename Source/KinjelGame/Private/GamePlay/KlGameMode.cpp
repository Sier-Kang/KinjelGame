// Fill out your copyright notice in the Description page of Project Settings.

#include "KlGameMode.h"
#include "FKlHelper.h"
#include "Data/FKlDataHandle.h"
#include "KlGameInstance.h"
#include "Kismet/GameplayStatics.h"

AKlGameMode::AKlGameMode()
{

}

void AKlGameMode::BeginPlay()
{
	FKlHelper::Debug(FString("DataHandle: ") + FKlDataHandle::Get()->RecordName, 30.f);

	Cast<UKlGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->GameName;
}
