// Fill out your copyright notice in the Description page of Project Settings.

#include "KlEnemyCharacter.h"
#include "Enemy/KlEnemyController.h"
#include "Components/CapsuleComponent.h"
#include "ConstructorHelpers.h"
#include "Engine/SkeletalMesh.h"
#include "Animation/AnimInstance.h"
#include "Components/ChildActorComponent.h"

// Sets default values
AKlEnemyCharacter::AKlEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Bind AI Controller
	AIControllerClass = AKlEnemyController::StaticClass();

	// Collision settings
	GetCapsuleComponent()->SetCollisionProfileName(FName("EnemyProfile"));
	GetCapsuleComponent()->SetGenerateOverlapEvents(true);

	// Add Skeletal Mesh
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> StaticEnemyMesh(
		TEXT("SkeletalMesh'/Game/Res/PolygonAdventure/Mannequin/Enemy/SkMesh/Enemy.Enemy'")
	);
	GetMesh()->SetSkeletalMesh(StaticEnemyMesh.Object);
	GetMesh()->SetCollisionObjectType(ECC_Pawn);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetCollisionResponseToAllChannels(ECR_Ignore);
	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -95.f));
	GetMesh()->SetRelativeRotation(FQuat::MakeFromEuler(FVector(0.f, 0.f, -90.f)));

	// Add Skeletal Mesh Animation
	static ConstructorHelpers::FClassFinder<UAnimInstance> StaticEnemyAnim(
		TEXT("AnimBlueprint'/Game/Blueprint/Enemy/Enemy_Anim.Enemy_Anim_C'")
	);
	GetMesh()->AnimClass = StaticEnemyAnim.Class;


	// Initialize socket
	WeaponSocket = CreateDefaultSubobject<UChildActorComponent>(TEXT("WeaponSocket"));

	ShieldSocket = CreateDefaultSubobject<UChildActorComponent>(TEXT("SheildSocket"));
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

