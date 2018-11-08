// Fill out your copyright notice in the Description page of Project Settings.

#include "KlPickupObject.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Data/FKlDataHandle.h"
#include "Engine/Engine.h"


// Sets default values
AKlPickupObject::AKlPickupObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	RootComponent = RootScene;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetupAttachment(RootScene);
	BaseMesh->SetCollisionProfileName(FName("PickUpProfile"));

	BaseMesh->SetGenerateOverlapEvents(true);
}

// Called when the game starts or when spawned
void AKlPickupObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKlPickupObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FText AKlPickupObject::GetInfoText() const
{
	TSharedPtr<ObjectAttribute> ObjectAttr = *FKlDataHandle::Get()->ObjectAttrMap.Find(ObjectIndex);

	switch (FKlDataHandle::Get()->CurrentCulture)
	{
	case ECultureTeam::EN:
		return ObjectAttr->EN;
	
	case ECultureTeam::ZH:
		return ObjectAttr->ZH;
	}

	return FText::FromString(" ");
}

int AKlPickupObject::TakePickup()
{
	BaseMesh->SetCollisionResponseToAllChannels(ECR_Ignore);

	if (GetWorld()) GetWorld()->DestroyActor(this);

	return ObjectIndex;
}

