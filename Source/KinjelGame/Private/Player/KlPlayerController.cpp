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
	if (!KlPlayerState)
	{
		KlPlayerState = Cast<AKlPlayerState>(PlayerState);
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

	CurrentUIType = EGameUIType::Game;
}

void AKlPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// View ray cast
	RunRayCast();

	// Update state machine
	StateMachine();

	// Update mini map
	TickMiniMap();
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

	// Bind Escape Event, keep running when pause game
	InputComponent->BindAction("EscEvent", IE_Pressed, this, &AKlPlayerController::EscEvent).bExecuteWhenPaused = true;

	// Bind Package Event
	InputComponent->BindAction("PackageEvent", IE_Pressed, this, &AKlPlayerController::PackageEvent);

	// Bind  ChatRoom Event
	InputComponent->BindAction("ChatRoomEvent", IE_Pressed, this, &AKlPlayerController::ChatRoomEvent);

	// Bind change mini map's size Event
	InputComponent->BindAction("AddMapSize", IE_Pressed, this, &AKlPlayerController::AddMapSizeStart);
	InputComponent->BindAction("AddMapSize", IE_Released, this, &AKlPlayerController::AddMapSizeStop);
	InputComponent->BindAction("ReduceMapSize", IE_Pressed, this, &AKlPlayerController::ReduceMapSizeStart);
	InputComponent->BindAction("ReduceMapSize", IE_Released, this, &AKlPlayerController::ReduceMapSizeStop);
}

void AKlPlayerController::ChangeHandObject()
{
	PlayerCharacter->ChangeHandObject(
		AKlHandObject::SpawnHandObject(
			Cast<AKlPlayerState>(PlayerState)->GetCurrentHandObjectIndex()
		)
	);
}

void AKlPlayerController::PlayerDead()
{
	// Change to third person view
	PlayerCharacter->ChangeView(EGameViewMode::Third);

	float DeadDuration = PlayerCharacter->PlayDeadAnim();

	LockedInput(true);

	FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(this, &AKlPlayerController::DeadTimeOut);

	GetWorld()->GetTimerManager().SetTimer(DeadHandle, TimerDelegate, DeadDuration, false);
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
	if (PlayerCharacter->IsInputLocked) return;

	PlayerCharacter->UpperBodyMode = LeftUpperType;

	bIsLeftButtonDown = true;
}

void AKlPlayerController::LeftEventStop()
{
	if (PlayerCharacter->IsInputLocked) return;

	PlayerCharacter->UpperBodyMode = EUpperBody::None;

	bIsLeftButtonDown = false;
}

void AKlPlayerController::RightEventStart()
{
	if (PlayerCharacter->IsInputLocked) return;

	// FKlHelper::Debug(FString("Right Event start....l"), 10.f);
	PlayerCharacter->UpperBodyMode = RightUpperType;

	bIsRightButtonDown = true;
}

void AKlPlayerController::RightEventStop()
{
	if (PlayerCharacter->IsInputLocked) return;

	PlayerCharacter->UpperBodyMode = EUpperBody::None;

	bIsRightButtonDown = false;
}

void AKlPlayerController::ScrollUpEvent()
{
	if (PlayerCharacter->IsInputLocked) return;

	if (!PlayerCharacter->bAllowedSwitchViewMode) return;

	if (bIsLeftButtonDown || bIsRightButtonDown) return;

	Cast<AKlPlayerState>(PlayerState)->ChangeShotcut(true);

	ChangeHandObject();
}

void AKlPlayerController::ScrollDownEvent()
{
	if (PlayerCharacter->IsInputLocked) return;

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
		//DrawRayLine(TraceStart, TraceEnd, 5.f);
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

	if (!IsDetected)
	{
		Cast<AKlPlayerState>(PlayerState)->RayInfoText = FText();
	}
}

void AKlPlayerController::StateMachine()
{
	// temp code
	ChangePreUpperType(EUpperBody::None);

	if (!Cast<AKlResourceObject>(RayCastActor) && !Cast<AKlPickupObject>(RayCastActor))
	{
		UpdatePointer.ExecuteIfBound(false, 1.f);
	}

	if (Cast<AKlResourceObject>(RayCastActor))
	{
		// Left button of mouse if pressed
		if (!bIsLeftButtonDown)
		{
			UpdatePointer.ExecuteIfBound(false, 0.f);
		}
		if (bIsLeftButtonDown && 
			FVector::Distance(RayCastActor->GetActorLocation(), PlayerCharacter->GetActorLocation()) < 
			Cast<AKlPlayerState>(PlayerState)->GetAffectRange())
		{
			// Get tool damage
			int Damage = Cast<AKlPlayerState>(PlayerState)->GetDamageValue(
				Cast<AKlResourceObject>(RayCastActor)->GetResourceType()
			);
			// RayCastActor take damage, and get HP percent value
			float Range = Cast<AKlResourceObject>(RayCastActor)->TakeObjectDamage(Damage)->GetHPRange();

			UpdatePointer.ExecuteIfBound(true, Range);
		}
	}
	// Ray cast Pickup object
	if (Cast<AKlPickupObject>(RayCastActor) &&
			FVector::Distance(RayCastActor->GetActorLocation(), PlayerCharacter->GetActorLocation()) < 300.f)
	{
		// Change right button of mouse's state
		ChangePreUpperType(EUpperBody::PickUp);

		UpdatePointer.ExecuteIfBound(false, 0);

		// Right button down of the mouse
		if (bIsRightButtonDown && 
			PlayerCharacter->IsPackageFree(Cast<AKlPickupObject>(RayCastActor)->ObjectIndex)) 
		{
			PlayerCharacter->AddPackageObject(Cast<AKlPickupObject>(RayCastActor)->TakePickup());
		}
	}
}

void AKlPlayerController::EscEvent()
{
	switch (CurrentUIType)
	{
	case EGameUIType::Game:
		// Set pause
		SetPause(true);
		// Set game mode to GameAndUI
		SwitchInputMode(false);
		// Update game ui
		ShowGameUI.ExecuteIfBound(CurrentUIType, EGameUIType::Pause);
		// Set current game ui
		CurrentUIType = EGameUIType::Pause;
		// Lock game input
		LockedInput(true);

		break;
	case EGameUIType::Pause:
	case EGameUIType::Package:
	case EGameUIType::ChatRoom:
		// Unlock pause
		SetPause(false);
		// Set game mode to Game
		SwitchInputMode(true);
		// Update Game UI
		ShowGameUI.ExecuteIfBound(CurrentUIType, EGameUIType::Game);
		// Update current UI
		CurrentUIType = EGameUIType::Game;
		// Unlocked Input
		LockedInput(false);

		break;
	}
}

void AKlPlayerController::PackageEvent()
{
	switch (CurrentUIType)
	{
	case EGameUIType::Game:
		SwitchInputMode(false);
		ShowGameUI.ExecuteIfBound(CurrentUIType, EGameUIType::Package);
		CurrentUIType = EGameUIType::Package;
		LockedInput(true);

		break;
	case EGameUIType::Package:
		SwitchInputMode(true);
		ShowGameUI.ExecuteIfBound(CurrentUIType, EGameUIType::Game);
		CurrentUIType = EGameUIType::Game;
		LockedInput(false);

		break;
	}
}

void AKlPlayerController::ChatRoomEvent()
{
	switch (CurrentUIType)
	{
	case EGameUIType::Game:
		SwitchInputMode(false);
		ShowGameUI.ExecuteIfBound(CurrentUIType, EGameUIType::ChatRoom);
		CurrentUIType = EGameUIType::ChatRoom;
		LockedInput(true);

		break;
	case EGameUIType::ChatRoom:
		SwitchInputMode(true);
		ShowGameUI.ExecuteIfBound(CurrentUIType, EGameUIType::Game);
		CurrentUIType = EGameUIType::Game;
		LockedInput(false);

		break;
	}
}

void AKlPlayerController::SwitchInputMode(bool bIsGameOnly)
{
	if (bIsGameOnly)
	{
		// Hide mouse cursor
		bShowMouseCursor = false;
		// Set Game Mode to OnlyGame
		FInputModeGameOnly InputMode;
		InputMode.SetConsumeCaptureMouseDown(true);
		SetInputMode(InputMode);
	}
	else
	{
		// Display mouse cursor
		bShowMouseCursor = true;
		// Set Game Mode to GameAndUI
		FInputModeGameAndUI InputMode;
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
		InputMode.SetHideCursorDuringCapture(false);
		SetInputMode(InputMode);
	}
}

void AKlPlayerController::LockedInput(bool bLockedInput)
{
	PlayerCharacter->IsInputLocked = bLockedInput;
}

void AKlPlayerController::AddMapSizeStart()
{
	if (PlayerCharacter->IsInputLocked) return;

	MiniMapSizeMode = EMiniMapSizeMode::Add;
}

void AKlPlayerController::AddMapSizeStop()
{
	if (PlayerCharacter->IsInputLocked) return;

	MiniMapSizeMode = EMiniMapSizeMode::None;
}

void AKlPlayerController::ReduceMapSizeStart()
{
	if (PlayerCharacter->IsInputLocked) return;

	MiniMapSizeMode = EMiniMapSizeMode::Reduce;
}

void AKlPlayerController::ReduceMapSizeStop()
{
	if (PlayerCharacter->IsInputLocked) return;

	MiniMapSizeMode = EMiniMapSizeMode::None;
}

void AKlPlayerController::TickMiniMap()
{
	switch (MiniMapSizeMode)
	{
	case EMiniMapSizeMode::Add:
		UpdateMiniMapWidth.ExecuteIfBound(5);

		break;
	case EMiniMapSizeMode::Reduce:
		UpdateMiniMapWidth.ExecuteIfBound(-5);

		break;
	}
}

void AKlPlayerController::DeadTimeOut()
{
	SetPause(true);

	SwitchInputMode(false);

	ShowGameUI.ExecuteIfBound(CurrentUIType, EGameUIType::Lose);

	CurrentUIType = EGameUIType::Lose;

	LockedInput(true);
}

