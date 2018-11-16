// Fill out your copyright notice in the Description page of Project Settings.

#include "KlEnemyTool.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "EnemyTool/KlEnemyWeapon.h"
#include "EnemyTool/KlEnemyShield.h"

// Sets default values
AKlEnemyTool::AKlEnemyTool()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Initialize root scene component
	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	RootComponent = RootScene;

	// Initialize BaseMesh, but no bind
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetupAttachment(RootComponent);
	BaseMesh->SetCollisionProfileName(FName("NoCollision"));

	// Initialize collision component
	AffectCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("AffectCollision"));
	AffectCollision->SetupAttachment(BaseMesh);
	AffectCollision->SetCollisionProfileName(FName("EnemeyToolProfile"));

	AffectCollision->SetGenerateOverlapEvents(false);

	// Bind event to overlap delegate
	FScriptDelegate OverlayBegin;
	OverlayBegin.BindUFunction(this, "OnOverlayBegin");
	AffectCollision->OnComponentBeginOverlap.Add(OverlayBegin);

	FScriptDelegate OverlayEnd;
	OverlayEnd.BindUFunction(this, "OnOverlayEnd");
	AffectCollision->OnComponentEndOverlap.Add(OverlayEnd);
}

// Called when the game starts or when spawned
void AKlEnemyTool::BeginPlay()
{
	Super::BeginPlay();
	
}

void AKlEnemyTool::OnOverlayBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{

}

void AKlEnemyTool::OnOverlayEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

// Called every frame
void AKlEnemyTool::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AKlEnemyTool::ChangeOverlapDetect(bool IsOpen)
{
	AffectCollision->SetGenerateOverlapEvents(IsOpen);
}

TSubclassOf<AActor> AKlEnemyTool::SpawnEnemyWeapon()
{
	return AKlEnemyWeapon::StaticClass();
}

TSubclassOf<AActor> AKlEnemyTool::SpawnEnemyShield()
{
	return AKlEnemyShield::StaticClass();
}

