// Fill out your copyright notice in the Description page of Project Settings.

#include "KlPlayerCharacter.h"
#include "ConstructorHelpers.h"
#include "Engine/SkeletalMesh.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
AKlPlayerCharacter::AKlPlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseTurnRate = 45.f;

	BaseLookUpRate = 45.f;

	CharacterViewMode = EGameViewMode::Third;

	GetCharacterMovement()->MaxWalkSpeed = 150.f;

	// Set capsule component's collision property
	GetCapsuleComponent()->SetCollisionProfileName(FName("PlayerProfile"));
	
	// Set first skeletal mesh to the default mesh component
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> StaticMeshFirst(
		TEXT("SkeletalMesh'/Game/Res/PolygonAdventure/Mannequin/FirstPlayer/SkMesh/FirstPlayer.FirstPlayer'")
	);
	MeshFirst = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshFirst"));
	MeshFirst->SetSkeletalMesh(StaticMeshFirst.Object);
	MeshFirst->SetupAttachment((USceneComponent*)GetCapsuleComponent());
	MeshFirst->bOnlyOwnerSee = true;
	MeshFirst->bCastDynamicShadow = false;
	MeshFirst->bReceivesDecals = false;

	// Set update frequincy
	MeshFirst->MeshComponentUpdateFlag = EMeshComponentUpdateFlag::OnlyTickPoseWhenRendered;
	MeshFirst->PrimaryComponentTick.TickGroup = TG_PrePhysics;

	// Set collision properties
	MeshFirst->SetCollisionObjectType(ECC_Pawn);
	MeshFirst->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshFirst->SetCollisionResponseToAllChannels(ECR_Ignore);

	MeshFirst->SetRelativeLocation(FVector(0.f, 0.f, -95.f));
	MeshFirst->SetRelativeRotation(FQuat::MakeFromEuler(FVector(0.f, 0.f, -90.f)));

	// Set first person's animation blueprint
	static ConstructorHelpers::FClassFinder<UAnimInstance> StaticAnimFirst(
		TEXT("AnimBlueprint'/Game/Blueprint/Player/FirstPalyer_Animation.FirstPalyer_Animation_C'")
	);
	MeshFirst->AnimClass = StaticAnimFirst.Class;

	// Set third skeletal mesh to the default mesh component
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> StaticMeshThird(
		TEXT("SkeletalMesh'/Game/Res/PolygonAdventure/Mannequin/Player/SkMesh/Player.Player'")
	);

	GetMesh()->SetSkeletalMesh(StaticMeshThird.Object);
	GetMesh()->bOnlyOwnerSee = true;
	GetMesh()->bReceivesDecals = false;
	GetMesh()->SetCollisionObjectType(ECC_Pawn);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetCollisionResponseToAllChannels(ECR_Ignore);

	// Set character's relative position and orientation
	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -95.f));
	GetMesh()->SetRelativeRotation(FQuat::MakeFromEuler(FVector(0.f, 0.f, -90.f)));

	// Set third person's animation blueprint
	static ConstructorHelpers::FClassFinder<UAnimInstance> StaticAnimThird(
		TEXT("AnimBlueprint'/Game/Blueprint/Player/ThirdPlayer_Animation.ThirdPlayer_Animation_C'")
	);
	GetMesh()->AnimClass = StaticAnimThird.Class;

	// Camera spring boom
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	// Set arm length
	CameraBoom->TargetArmLength = 300.f;
	CameraBoom->TargetOffset = FVector(0.f, 0.f, 60.f);
	// Bind to Controller's rotation
	CameraBoom->bUsePawnControlRotation = true;

	// Third person's camera
	ThirdCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ThirdCamera"));
	ThirdCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	ThirdCamera->bUsePawnControlRotation = false;

	// First person's camera
	FirstCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstCamera"));
	FirstCamera->SetupAttachment(RootComponent);
	FirstCamera->bUsePawnControlRotation = true;
	FirstCamera->AddLocalOffset(FVector(0.f, 0.f, 60.f));

	// Set visible
	FirstCamera->SetActive(false);
	ThirdCamera->SetActive(true);
	
	MeshFirst->SetOwnerNoSee(true);
	GetMesh()->SetOwnerNoSee(false);
}

// Called when the game starts or when spawned
void AKlPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKlPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AKlPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AKlPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AKlPlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &AKlPlayerCharacter::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &AKlPlayerCharacter::LookUpAtRate);
	PlayerInputComponent->BindAxis("TurnRate", this, &AKlPlayerCharacter::TurnAtRate);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AKlPlayerCharacter::OnStartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AKlPlayerCharacter::OnStopJump);
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &AKlPlayerCharacter::OnStartRun);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &AKlPlayerCharacter::OnStopRun);
}

void AKlPlayerCharacter::ChangeView(EGameViewMode::Type NewCharacterView)
{
	CharacterViewMode = NewCharacterView;

	switch (NewCharacterView)
	{
	case EGameViewMode::First:
		FirstCamera->SetActive(true);
		ThirdCamera->SetActive(false);
		MeshFirst->SetOwnerNoSee(false);
		GetMesh()->SetOwnerNoSee(true);

		break;
	case EGameViewMode::Third:
		FirstCamera->SetActive(false);
		ThirdCamera->SetActive(true);
		MeshFirst->SetOwnerNoSee(true);
		GetMesh()->SetOwnerNoSee(false);

		break;
	default:

		break;
	}
}

void AKlPlayerCharacter::MoveForward(float Value)
{
	if (Value != 0.f && Controller) {
		const FRotator Rotation = Controller->GetControlRotation();
		FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AKlPlayerCharacter::MoveRight(float Value)
{
	if (Value != 0) {
		const FQuat Rotation = GetActorQuat();
		FVector Direction = FQuatRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void AKlPlayerCharacter::LookUpAtRate(float Value)
{
	AddControllerPitchInput(Value *BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AKlPlayerCharacter::Turn(float Value)
{
	AddControllerYawInput(Value);
}

void AKlPlayerCharacter::TurnAtRate(float Value)
{
	AddControllerYawInput(Value *BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AKlPlayerCharacter::OnStartJump()
{
	bPressedJump = true;
}

void AKlPlayerCharacter::OnStopJump()
{
	bPressedJump = false;
	StopJumping();
}

void AKlPlayerCharacter::OnStartRun()
{
	GetCharacterMovement()->MaxWalkSpeed = 375.f;
}

void AKlPlayerCharacter::OnStopRun()
{
	GetCharacterMovement()->MaxWalkSpeed = 150.f;
}

