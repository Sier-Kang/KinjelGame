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
#include "KlPlayerCharacter.h"
#include "Engine/EngineTypes.h"


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

	if (!GetWorld()) return;

	// Register detect timer event
	FTimerDelegate DetectPlayerDele;
	DetectPlayerDele.BindUObject(this, &AKlFlobObject::DetectPlayer);

	GetWorld()->GetTimerManager().SetTimer(DetectTimer, DetectPlayerDele, 1.f, true, 3.f);

	// Register destroy timer event
	FTimerDelegate DestroyDele;
	DestroyDele.BindUObject(this, &AKlFlobObject::DestroyEvent);

	GetWorld()->GetTimerManager().SetTimer(DestroyTimer, DestroyDele, 30.f, false);

	PlayerCharacter = nullptr;
}

void AKlFlobObject::RenderTexture()
{
	TSharedPtr<ObjectAttribute> ObjectAttr = *FKlDataHandle::Get()->ObjectAttrMap.Find(ObjectIndex);
	ObjectIconTex = LoadObject<UTexture>(NULL, *ObjectAttr->TexPath);

	ObjectIconMatDynamic->SetTextureParameterValue(FName("ObjectTex"), ObjectIconTex);

	BaseMesh->SetMaterial(0, ObjectIconMatDynamic);
}

void AKlFlobObject::DetectPlayer()
{
	if (!GetWorld()) return;

	// Saving result
	TArray<FOverlapResult> Overlaps;
	FCollisionObjectQueryParams ObjectParams;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.bTraceAsyncScene = true;

	// Dynamic detection, 200 range, return true if query success
	if (GetWorld()->OverlapMultiByObjectType(Overlaps, GetActorLocation(), FQuat::Identity, ObjectParams, FCollisionShape::MakeSphere(200.f), Params))
	{
		for (TArray<FOverlapResult>::TIterator It(Overlaps); It; ++It) {
			// Detect player character
			if (Cast<AKlPlayerCharacter>(It->GetActor())) {
				// Assignment
				PlayerCharacter = Cast<AKlPlayerCharacter>(It->GetActor());
				// Package
				if (true)
				{
					// Pause detection
					GetWorld()->GetTimerManager().PauseTimer(DetectTimer);

					// Pause destroy
					GetWorld()->GetTimerManager().PauseTimer(DestroyTimer);

					// Close physics
					BoxCollision->SetSimulatePhysics(false);
				}

				return;
			}
		}
	}
}

void AKlFlobObject::DestroyEvent()
{
	if (!GetWorld()) return;

	// UnRegister Timer handle
	GetWorld()->GetTimerManager().ClearTimer(DetectTimer);
	GetWorld()->GetTimerManager().ClearTimer(DestroyTimer);

	// Destroy itself
	GetWorld()->DestroyActor(this);
}

// Called every frame
void AKlFlobObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Keeping rotaiton
	BaseMesh->AddLocalRotation(FRotator(DeltaTime * 60.f, 0.f, 0.f));

	// If detect palyer character
	if (PlayerCharacter) {
		// Close to player
		SetActorLocation(FMath::VInterpTo(GetActorLocation(), 
			PlayerCharacter->GetActorLocation() + FVector(0.f, 0.f, 40.f), DeltaTime, 5.f));

		// Distance approximate to 0
		if (FVector::Distance(GetActorLocation(), PlayerCharacter->GetActorLocation() + FVector(0.f, 0.f, 40.f)) < 10.f)
		{
			if (true) {
				//PlayerCharacter->AddPackageObject(ObjectIndex);
				// Destroy
				DestroyEvent();
			}
			else {
				PlayerCharacter = nullptr;

				GetWorld()->GetTimerManager().UnPauseTimer(DetectTimer);

				GetWorld()->GetTimerManager().UnPauseTimer(DestroyTimer);

				BoxCollision->SetSimulatePhysics(true);
			}
		}
	}
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

