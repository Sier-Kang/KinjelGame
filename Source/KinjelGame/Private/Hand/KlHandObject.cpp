// Fill out your copyright notice in the Description page of Project Settings.

#include "KlHandObject.h"
#include "Components/StaticMeshComponent.h"
#include "ConstructorHelpers.h"
#include "Engine/StaticMesh.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "KlHandNone.h"
#include "KlHandWood.h"
#include "KlHandStone.h"
#include "KlHandApple.h"
#include "KlHandMeat.h"
#include "KlHandAxe.h"
#include "KlHandHammer.h"
#include "KlHandSword.h"
#include "FKlHelper.h"


// Sets default values
AKlHandObject::AKlHandObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Initialize root scene
	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	RootComponent = RootScene;

	// Initialize object mesh instance
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetupAttachment(RootScene);
	BaseMesh->SetCollisionProfileName(FName("NoCollision"));

	// Initialize object collision box.
	AffectCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("AffectCollision"));
	AffectCollision->SetupAttachment(RootScene);
	AffectCollision->SetCollisionProfileName(FName("ToolProfile"));

	// Close overlap query(¼ì²â) when begin
	AffectCollision->SetGenerateOverlapEvents(false);

	FScriptDelegate OverlayBegin;
	OverlayBegin.BindUFunction(this, FName("OnOverlayBegin"));
	AffectCollision->OnComponentBeginOverlap.Add(OverlayBegin);
	
	FScriptDelegate OverlayEnd;
	OverlayEnd.BindUFunction(this, FName("OnOverlayEnd"));
	AffectCollision->OnComponentEndOverlap.Add(OverlayEnd);
}

// Called when the game starts or when spawned
void AKlHandObject::BeginPlay()
{
	Super::BeginPlay();
	
}

void AKlHandObject::OnOverlayBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	FKlHelper::Debug(FString("OverlayBegin"), 3.f);
}

void AKlHandObject::OnOverlayEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	FKlHelper::Debug(FString("OverlayEnd"), 3.f);
}

// Called every frame
void AKlHandObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

TSubclassOf<AActor> AKlHandObject::SpawnHandObject(int ObjectID)
{
	switch (ObjectID)
	{
	case 0:
		return AKlHandNone::StaticClass();

	case 1:
		return AKlHandWood::StaticClass();

	case 2:
		return AKlHandStone::StaticClass();

	case 3:
		return AKlHandApple::StaticClass();

	case 4:
		return AKlHandMeat::StaticClass();

	case 5:
		return AKlHandAxe::StaticClass();

	case 6:
		return AKlHandHammer::StaticClass();

	case 7:
		return AKlHandSword::StaticClass();
	}

	return AKlHandNone::StaticClass();
}

void AKlHandObject::ChangeOverlayDetect(bool IsOpen)
{
	AffectCollision->SetGenerateOverlapEvents(IsOpen);
}
