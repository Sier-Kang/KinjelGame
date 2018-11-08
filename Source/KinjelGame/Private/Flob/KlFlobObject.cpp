// Fill out your copyright notice in the Description page of Project Settings.

#include "KlFlobObject.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "ConstructorHelpers.h"
#include "Engine/StaticMesh.h"
#include "Data/FKlDataHandle.h"
#include "TimerManager.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/MaterialInterface.h"
#include "RandomStream.h"


// Sets default values
AKlFlobObject::AKlFlobObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	RootComponent = (USceneComponent*)BoxCollision;
	BoxCollision->SetCollisionProfileName(FName("FlobProfile"));
	// Open PhsX
	BoxCollision->SetSimulatePhysics(true);
	BoxCollision->SetConstraintMode(EDOFMode::Default);
	BoxCollision->GetBodyInstance()->bLockRotation = true;
	BoxCollision->SetBoxExtent(FVector(15.f));

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticBaseMesh(
		TEXT("StaticMesh'/Engine/BasicShapes/Plane.Plane'")
	);
	BaseMesh->SetStaticMesh(StaticBaseMesh.Object);
	BaseMesh->SetCollisionResponseToChannels(ECR_Ignore);
	BaseMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// Set transform
	BaseMesh->SetRelativeRotation(FRotator(0.f, 0.f, 90.f));
	BaseMesh->SetRelativeScale3D(FVector(0.3f));

	UMaterialInterface* StaticObjectIconMat = LoadObject<UMaterialInterface>(
		NULL, 
		TEXT("MaterialInstanceConstant'/Game/Material/FlobIconMat_Inst.FlobIconMat_Inst'")
	);
	// Create dynamic material
	ObjectIconMatDynamic = UMaterialInstanceDynamic::Create(StaticObjectIconMat, nullptr);
}

// Called when the game starts or when spawned
void AKlFlobObject::BeginPlay()
{
	Super::BeginPlay();
	
}

void AKlFlobObject::RenderTexture()
{
	TSharedPtr<ObjectAttribute> ObjectAttr = *FKlDataHandle::Get()->ObjectAttrMap.Find(ObjectIndex);
	ObjectIconTex = LoadObject<UTexture>(NULL, *ObjectAttr->TexPath);

	ObjectIconMatDynamic->SetTextureParameterValue(FName("ObjectTex"), ObjectIconTex);

	BaseMesh->SetMaterial(0, ObjectIconMatDynamic);
}

// Called every frame
void AKlFlobObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AKlFlobObject::CreateFlobObject(int ObjectID)
{
	ObjectIndex = ObjectID;

	RenderTexture();

	// Random force
	FRandomStream Stream;
	Stream.GenerateNewSeed();

	int DirYaw = Stream.RandRange(-180, 180);
	FRotator ForceRot = FRotator(0.f, DirYaw, 0.f);

	// Add force
	BoxCollision->AddForce((FVector(0.f, 0.f, 4.f) + ForceRot.Vector()) * 100000.f);
}

