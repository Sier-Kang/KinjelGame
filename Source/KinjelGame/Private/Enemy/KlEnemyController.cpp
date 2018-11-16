// Fill out your copyright notice in the Description page of Project Settings.

#include "KlEnemyController.h"
#include "Player/KlPlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Enemy/KlEnemyCharacter.h"

AKlEnemyController::AKlEnemyController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AKlEnemyController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AKlEnemyController::OnSeePlayer()
{
	// Set Lock player
	IsLockPlayer = true;

	// Change character's max speed
	EnemyCharacter->SetMaxSpeed(300.f);
}

FVector AKlEnemyController::GetPlayerLocation() const
{
	if (PlayerCharacter)
	{
		return PlayerCharacter->GetActorLocation();
	}

	return FVector::ZeroVector;
}

void AKlEnemyController::BeginPlay()
{
	Super::BeginPlay();

	IsLockPlayer = false;

	// Set reference
	PlayerCharacter = Cast<AKlPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	EnemyCharacter = Cast<AKlEnemyCharacter>(GetPawn());
}
