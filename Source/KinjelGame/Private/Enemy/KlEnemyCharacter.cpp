// Fill out your copyright notice in the Description page of Project Settings.

#include "KlEnemyCharacter.h"
#include "Enemy/KlEnemyController.h"
#include "Components/CapsuleComponent.h"
#include "ConstructorHelpers.h"
#include "Engine/SkeletalMesh.h"
#include "Animation/AnimInstance.h"
#include "Components/ChildActorComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnemyTool/KlEnemyTool.h"
#include "UI/Widgets/SKlEnemyHPWidget.h"
#include "Components/WidgetComponent.h"
#include "KlPlayerCharacter.h"
#include "Enemy/KlEnemyAnim.h"
#include "Enemy/KlEnemyController.h"


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

	// Set HP Bar Widget
	HPBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBar"));
	HPBar->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AKlEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Get reference
	EnemyController = Cast<AKlEnemyController>(GetController());

	EnemyAnimInst = Cast<UKlEnemyAnim>(GetMesh()->GetAnimInstance());
	
	// Bind enemy tool to skeletal mesh sockets
	WeaponSocket->AttachToComponent(GetMesh(), 
		FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("RHSocket"));

	ShieldSocket->AttachToComponent(GetMesh(), 
		FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("LHSocket"));

	// Add tool to socket
	WeaponSocket->SetChildActorClass(AKlEnemyTool::SpawnEnemyWeapon());
	ShieldSocket->SetChildActorClass(AKlEnemyTool::SpawnEnemyShield());

	SAssignNew(HPBarWidget, SKlEnemyHPWidget);
	HPBar->SetSlateWidget(HPBarWidget);
	HPBar->SetRelativeLocation(FVector(0.f, 0.f, 100.f));
	HPBar->SetDrawSize(FVector2D(100.f, 10.f));

	HP = 200.f;
	HPBarWidget->ChangeHP(HP / 200.f);
}

void AKlEnemyCharacter::OnSeePlayer(APawn* PlayerChar)
{
	if (Cast<AKlPlayerCharacter>(PlayerChar)) {

		// Notify the controller OnSeePlayer event
		if (EnemyController) EnemyController->OnSeePlayer();
	}
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

void AKlEnemyCharacter::SetMaxSpeed(float Speed)
{
	GetCharacterMovement()->MaxWalkSpeed = Speed;
}

