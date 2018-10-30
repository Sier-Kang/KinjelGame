// Fill out your copyright notice in the Description page of Project Settings.

#include "KlPlayerCharacter.h"


// Sets default values
AKlPlayerCharacter::AKlPlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AKlPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKlPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AKlPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

