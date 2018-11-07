// Fill out your copyright notice in the Description page of Project Settings.

#include "KlPlayerController.h"
#include "Player/KlPlayerCharacter.h"
#include "FKlHelper.h"
#include "KlPlayerState.h"
#include "KlHandObject.h"
#include "Components/LineBatchComponent.h"
#include "KlPickupObject.h"
#include "KlResourceObject.h"

AKlPlayerController::AKlPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AKlPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (!PlayerCharacter)
	{
		PlayerCharacter = Cast<AKlPlayerCharacter>(GetCharacter());
	}

	// Set UI property etc and Input mode.
	bShowMouseCursor = false;
	FInputModeGameOnly InputMode;
	InputMode.SetConsumeCaptureMouseDown(true);
	SetInputMode(InputMode);

	// Set upper body status
	LeftUpperType = EUpperBody::Punch;
	RightUpperType = EUpperBody::PickUp;

	bIsLeftButtonDown = false;
	bIsRightButtonDown = false;
}

void AKlPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// temp code
	ChangePreUpperType(EUpperBody::None);

	// View ray cast
	RunRayCast();
}

void AKlPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Bind change view
	InputComponent->BindAction("ChangeView", IE_Pressed, this, &AKlPlayerController::ChangeView);
	InputComponent->BindAction("LeftEvent", IE_Pressed, this, &AKlPlayerController::LeftEventStart);
	InputComponent->BindAction("LeftEvent", IE_Released, this, &AKlPlayerController::LeftEventStop);
	InputComponent->BindAction("RightEvent", IE_Pressed, this, &AKlPlayerController::RightEventStart);
	InputComponent->BindAction("RightEvent", IE_Released, this, &AKlPlayerController::RightEventStop);

	InputComponent->BindAction("ScrollUp", IE_Pressed, this, &AKlPlayerController::ScrollUpEvent);
	InputComponent->BindAction("ScrollDown", IE_Pressed, this, &AKlPlayerController::ScrollDownEvent);
}

void AKlPlayerController::ChangeHandObject()
{
	PlayerCharacter->ChangeHandObject(
		AKlHandObject::SpawnHandObject(
			Cast<AKlPlayerState>(PlayerState)->GetCurrentHandObjectIndex()
		)
	);
}

void AKlPlayerController::ChangeView()
{
	if (!PlayerCharacter) return;

	// If do not allow to switch view mode, immediately return
	if (!PlayerCharacter->bAllowedSwitchViewMode) return;

	switch (PlayerCharacter->CharacterViewMode) 
	{
	case EGameViewMode::First:
		PlayerCharacter->ChangeView(EGameViewMode::Third);

		break;
	case EGameViewMode::Third:
		PlayerCharacter->ChangeView(EGameViewMode::First);

		break;
	default:

		break;
	}
}

void AKlPlayerController::LeftEventStart()
{
	PlayerCharacter->UpperBodyMode = LeftUpperType;

	bIsLeftButtonDown = true;
}

void AKlPlayerController::LeftEventStop()
{
	PlayerCharacter->UpperBodyMode = EUpperBody::None;

	bIsLeftButtonDown = false;
}

void AKlPlayerController::RightEventStart()
{
	// FKlHelper::Debug(FString("Right Event start....l"), 10.f);
	PlayerCharacter->UpperBodyMode = RightUpperType;

	bIsRightButtonDown = true;
}

void AKlPlayerController::RightEventStop()
{
	PlayerCharacter->UpperBodyMode = EUpperBody::None;

	bIsRightButtonDown = false;
}

void AKlPlayerController::ScrollUpEvent()
{
	if (!PlayerCharacter->bAllowedSwitchViewMode) return;

	if (bIsLeftButtonDown || bIsRightButtonDown) return;

	Cast<AKlPlayerState>(PlayerState)->ChangeShotcut(true);

	ChangeHandObject();
}

void AKlPlayerController::ScrollDownEvent()
{
	if (!PlayerCharacter->bAllowedSwitchViewMode) return;

	if (bIsLeftButtonDown || bIsRightButtonDown) return;

	Cast<AKlPlayerState>(PlayerState)->ChangeShotcut(false);

	ChangeHandObject();
}

void AKlPlayerController::ChangePreUpperType(EUpperBody::Type RightType = EUpperBody::None)
{
	// Change pre montage action according to current object type
	switch (Cast<AKlPlayerState>(PlayerState)->GetCurrentObjectType())
	{
	case EObjectType::Normal:
		LeftUpperType = EUpperBody::Punch;
		RightUpperType = RightType;

		break;
	case EObjectType::Food:
		LeftUpperType = EUpperBody::Punch;
		// If RightType is PickUp, then ignore Eat, for it has priority higher.
		RightUpperType = RightType == EUpperBody::None ? EUpperBody::Eat : RightType;

		break;
	case EObjectType::Tool:
		LeftUpperType = EUpperBody::Hit;
		RightUpperType = RightType;

		break;
	case EObjectType::Weapon:
		LeftUpperType = EUpperBody::Fight;
		RightUpperType = RightType;

		break;
	}
}

FHitResult AKlPlayerController::RayGetHitResult(FVector TraceStart, FVector TraceEnd)
{
	FCollisionQueryParams TraceParams(true);
	TraceParams.AddIgnoredActor(PlayerCharacter);
	TraceParams.bTraceAsyncScene = true;
	TraceParams.bReturnPhysicalMaterial = false;
	TraceParams.bTraceComplex = true;

	FHitResult HitResult(ForceInit);
	if (GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_GameTraceChannel1,
		TraceParams))
	{
		DrawRayLine(TraceStart, TraceEnd, 5.f);
		//FKlHelper::Debug(FString("Line info: ") + TraceStart.ToString() + FString("___") + TraceEnd.ToString(), 10.f);
	}

	return HitResult;
}

void AKlPlayerController::DrawRayLine(FVector StartPos, FVector EndPos, float Duration)
{
	ULineBatchComponent* LineBatcher = GetWorld()->PersistentLineBatcher;
	if (LineBatcher != nullptr)
	{
		float LineDuration = (Duration > 0.f) ? Duration : LineBatcher->DefaultLifeTime;
		LineBatcher->DrawLine(StartPos, EndPos, FLinearColor::Red, 10, 0.f, LineDuration);	
	}
}

void AKlPlayerController::RunRayCast()
{
	FVector StartPos(0.f);
	FVector EndPos(0.f);

	switch (PlayerCharacter->CharacterViewMode)
	{
	case EGameViewMode::First:
		StartPos = PlayerCharacter->FirstCamera->K2_GetComponentLocation();
		EndPos = StartPos + PlayerCharacter->FirstCamera->GetForwardVector()*2000.f;

		break;
	case EGameViewMode::Third:
		StartPos = PlayerCharacter->ThirdCamera->K2_GetComponentLocation();
		StartPos = StartPos + PlayerCharacter->ThirdCamera->GetForwardVector()*300.f;
		EndPos = StartPos + PlayerCharacter->ThirdCamera->GetForwardVector()*2000.f;

		break;
	default:
		break;
	}

	bool IsDetected = false;
	FHitResult HitResult = RayGetHitResult(StartPos, EndPos);
	RayCastActor = HitResult.GetActor();

	if (Cast<AKlPickupObject>(RayCastActor))
	{
		IsDetected = true;
		Cast<AKlPlayerState>(PlayerState)->RayInfoText =
			Cast<AKlPickupObject>(RayCastActor)->GetInfoText();
	}

	if (Cast<AKlResourceObject>(RayCastActor))
	{
		IsDetected = true;
		Cast<AKlPlayerState>(PlayerState)->RayInfoText =
			Cast<AKlResourceObject>(RayCastActor)->GetInfoText();
	}
}

