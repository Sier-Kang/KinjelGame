// Fill out your copyright notice in the Description page of Project Settings.

#include "KlHandObject.h"
#include "Components/StaticMeshComponent.h"
#include "ConstructorHelpers.h"
#include "Engine/StaticMesh.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"


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
	// AffectCollision->bGenerateOverlapEvents = false;
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

}

void AKlHandObject::OnOverlayEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

// Called every frame
void AKlHandObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

