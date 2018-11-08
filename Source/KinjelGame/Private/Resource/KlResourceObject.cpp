// Fill out your copyright notice in the Description page of Project Settings.

#include "KlResourceObject.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Data/FKlDataHandle.h"
#include "Engine/Engine.h"
#include "FKlHelper.h"


// Sets default values
AKlResourceObject::AKlResourceObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	RootComponent = RootScene;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetupAttachment(RootScene);
	BaseMesh->SetCollisionProfileName(FName("ResourceProfile"));

	BaseMesh->SetGenerateOverlapEvents(true);

	HP = BaseHP = 100;
}

// Called when the game starts or when spawned
void AKlResourceObject::BeginPlay()
{
	Super::BeginPlay();

	if (FKlDataHandle::Get()->ResourceAttrMap.Num() == 0)
	{
		FKlDataHandle::Get()->InitResourceAttr();
	}

	TSharedPtr<ResourceAttribute> ResourceAttr =
		*FKlDataHandle::Get()->ResourceAttrMap.Find(ResourceIndex);

	FKlHelper::Debug(ResourceAttr->ToString(), 30.f);

	HP = BaseHP = ResourceAttr->HP;
}

void AKlResourceObject::CreateFlobObject()
{
	TSharedPtr<ResourceAttribute> ResourceAttr = 
		*FKlDataHandle::Get()->ResourceAttrMap.Find(ResourceIndex);

	for (TArray<TArray<int>>::TIterator It(ResourceAttr->FlobObjectInfo); It; ++It) {
		// Random seed
		FRandomStream Stream;
		Stream.GenerateNewSeed();

		// Number of flob object
		int Num = Stream.RandRange((*It)[1], (*It)[2]);

		if (GetWorld()) {
			for (int i = 0; i < Num; ++i) {
				// Spawn flobs
				//ASlAiFlobObject* FlobObject = GetWorld()->SpawnActor<ASlAiFlobObject>(GetActorLocation() + FVector(0.f, 0.f, 20.f), FRotator::ZeroRotator);
				//FlobObject->CreateFlobObject((*It)[0]);
			}
		}
	}
}

// Called every frame
void AKlResourceObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FText AKlResourceObject::GetInfoText() const
{
	TSharedPtr<ResourceAttribute> ResourceAttr = 
		*FKlDataHandle::Get()->ResourceAttrMap.Find(ResourceIndex);

	switch (FKlDataHandle::Get()->CurrentCulture)
	{
	case ECultureTeam::EN:
		return ResourceAttr->EN;

		break;
	case ECultureTeam::ZH:
		return ResourceAttr->ZH;

		break;
	}

	return ResourceAttr->ZH;
}

EResourceType::Type AKlResourceObject::GetResourceType() const
{
	TSharedPtr<ResourceAttribute> ResourceAttr =
		*FKlDataHandle::Get()->ResourceAttrMap.Find(ResourceIndex);

	return ResourceAttr->ResourceType;
}

float AKlResourceObject::GetHPRange() const
{
	return FMath::Clamp<float>((float)HP / (float)BaseHP, 0.f, 1.f);
}

AKlResourceObject* AKlResourceObject::TakeObjectDamage(int Damage)
{
	HP = FMath::Clamp<int>(HP - Damage, 0, BaseHP);

	if (HP <= 0) {
		// Detect fail
		BaseMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
		// Create drop down object
		//CreateFlobObject();
		// Destroy object
		GetWorld()->DestroyActor(this);
	}

	return this;
}

