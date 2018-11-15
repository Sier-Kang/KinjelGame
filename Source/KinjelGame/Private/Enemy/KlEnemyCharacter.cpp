// Fill out your copyright notice in the Description page of Project Settings.

#include "KlEnemyCharacter.h"
#include "Enemy/KlEnemyController.h"

// Sets default values
AKlEnemyCharacter::AKlEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Bind AI Controller
	AIControllerClass = AKlEnemyController::StaticClass();
}

// Called when the game starts or when spawned
void AKlEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKlEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AKlEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

