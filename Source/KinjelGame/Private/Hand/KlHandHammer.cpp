// Fill out your copyright notice in the Description page of Project Settings.

#include "KlHandHammer.h"
#include "ConstructorHelpers.h"
#include "Engine/StaticMesh.h"
#include "Components/BoxComponent.h"
#include "Sound/SoundWave.h"

AKlHandHammer::AKlHandHammer()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticBaseMesh(
		TEXT("StaticMesh'/Game/Res/PolygonAdventure/Meshes/SM_Bld_FencePost_01.SM_Bld_FencePost_01'")
	);

	BaseMesh->SetStaticMesh(StaticBaseMesh.Object);

	// Add extend mesh object
	ExtendMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ExtendMesh"));
	ExtendMesh->SetupAttachment(RootComponent);
	ExtendMesh->SetCollisionProfileName(FName("NoCollision"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticExtendMesh(
		TEXT("StaticMesh'/Game/Res/PolygonAdventure/Meshes/SM_Prop_StoneBlock_01.SM_Prop_StoneBlock_01'")
	);
	ExtendMesh->SetStaticMesh(StaticExtendMesh.Object);

	BaseMesh->SetRelativeLocation(FVector(35.f, 0.f, 3.f));
	BaseMesh->SetRelativeRotation(FRotator(0.f, -90.f, -90.f));
	BaseMesh->SetRelativeScale3D(FVector(0.4f, 0.4f, 0.4f));

	ExtendMesh->SetRelativeLocation(FVector(33.f, 1.f, 3.f));
	ExtendMesh->SetRelativeRotation(FRotator(0.f, -90.f, -90.f));
	ExtendMesh->SetRelativeScale3D(FVector(0.4f, 0.4f, 0.4f));

	AffectCollision->SetRelativeLocation(FVector(26.f, 1.f, 3.f));
	AffectCollision->SetRelativeScale3D(FVector(0.22f, 0.44f, 0.31f));
}

void AKlHandHammer::BeginPlay()
{
	Super::BeginPlay();

	// Define object index
	ObjectIndex = 6;

	// Add hammer sound
	OverlaySound = LoadObject<USoundWave>(NULL, TEXT("SoundWave'/Game/Res/Sound/GameSound/Hammer.Hammer'"));
}
