// Fill out your copyright notice in the Description page of Project Settings.

#include "StrategyKitPrivatePCH.h"
#include "StrategyController.h"
#include "StrategyCameraComponent.h"
#include "StrategyPawn.h"
#include "TouchInput.h"
#include "TouchInputInterface.h"
#include "StrategyKitHelpers.h"


AStrategyController::AStrategyController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, bIgnoreInput(false)
{
	bShowMouseCursor = true;
	bObj3DDealSwipe = false;
}

//bool AStrategyController::InputTouch(uint32 Handle, ETouchType::Type Type, const FVector2D& TouchLocation, FDateTime DeviceTimestamp, uint32 TouchpadIndex)
//{
//	bool bResult = false;
//
//	if (PlayerInput)
//	{
//		bResult = PlayerInput->InputTouch(Handle, Type, TouchLocation, DeviceTimestamp, TouchpadIndex);
//	}
//
//	return bResult;
//}

void AStrategyController::ProcessPlayerInput(const float DeltaTime, const bool bGamePaused)
{
	if (!bGamePaused && PlayerInput && InputHandler && !bIgnoreInput)
	{
	//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("AStrategyController::ProcessPlayerInput"));
		InputHandler->UpdateDetection(DeltaTime);
	}
}

void AStrategyController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputHandler = NewObject<UTouchInput>(this);

	BIND_1P_ACTION(InputHandler, EGameKey::Tap, IE_Pressed, &AStrategyController::OnTapPressed);
	BIND_1P_ACTION(InputHandler, EGameKey::Hold, IE_Pressed, &AStrategyController::OnHoldPressed);
	BIND_1P_ACTION(InputHandler, EGameKey::Hold, IE_Released, &AStrategyController::OnHoldReleased);
	BIND_1P_ACTION(InputHandler, EGameKey::Swipe, IE_Pressed, &AStrategyController::OnSwipeStarted);
	BIND_1P_ACTION(InputHandler, EGameKey::Swipe, IE_Repeat, &AStrategyController::OnSwipeUpdate);
	BIND_1P_ACTION(InputHandler, EGameKey::Swipe, IE_Released, &AStrategyController::OnSwipeReleased);
	BIND_2P_ACTION(InputHandler, EGameKey::SwipeTwoPoints, IE_Pressed, &AStrategyController::OnSwipeTwoPointsStarted);
	BIND_2P_ACTION(InputHandler, EGameKey::SwipeTwoPoints, IE_Repeat, &AStrategyController::OnSwipeTwoPointsUpdate);
	BIND_2P_ACTION(InputHandler, EGameKey::Pinch, IE_Pressed, &AStrategyController::OnPinchStarted);
	BIND_2P_ACTION(InputHandler, EGameKey::Pinch, IE_Repeat, &AStrategyController::OnPinchUpdate);
}

void AStrategyController::OnTapPressed(const FVector2D& ScreenPosition, float DownTime)
{
	FVector WorldPosition(0.f);
	AActor* const HitActor = GetFriendlyTarget(ScreenPosition, WorldPosition);

	InputStartActor = HitActor;
	SetSelectedActor(HitActor, WorldPosition, ETouchInputEnum::VE_Tap);

	if (HitActor && HitActor->GetClass()->ImplementsInterface(UTouchInputInterface::StaticClass()))
	{
		ITouchInputInterface::Execute_OnInputTap(HitActor);
	}
}

void AStrategyController::OnHoldPressed(const FVector2D& ScreenPosition, float DownTime)
{
	FVector WorldPosition(0.0f);
	AActor* const HitActor = GetFriendlyTarget(ScreenPosition, WorldPosition);

	InputStartActor = HitActor;
	SetSelectedActor(HitActor, WorldPosition, ETouchInputEnum::VE_Hold);

	if (HitActor && HitActor->GetClass()->ImplementsInterface(UTouchInputInterface::StaticClass()))
	{
		ITouchInputInterface::Execute_OnInputHold(HitActor);
	}
}

void AStrategyController::OnHoldReleased(const FVector2D& ScreenPosition, float DownTime)
{
	AActor* const InputStart = InputStartActor.Get();
	if (InputStart && InputStart->GetClass()->ImplementsInterface(UTouchInputInterface::StaticClass()))
	{
		ITouchInputInterface::Execute_OnInputHoldReleased(InputStart, DownTime);
	}
}

void AStrategyController::OnSwipeStarted(const FVector2D& AnchorPosition, float DownTime)
{
	if (GetStrategyCameraComponent() != nullptr)
	{
		GetStrategyCameraComponent()->OnSwipeStarted(AnchorPosition, DownTime);
	}

	FVector WorldPosition(0.0f);
	AActor* const HitActor = GetFriendlyTarget(AnchorPosition, WorldPosition);
	InputStartActor = HitActor;
	SetSelectedActor(HitActor, WorldPosition, ETouchInputEnum::VE_Swipe);

	if (HitActor && HitActor->GetClass()->ImplementsInterface(UTouchInputInterface::StaticClass()))
	{
		SwipeAnchor3D = HitActor->GetActorLocation();
		bObj3DDealSwipe = ITouchInputInterface::Execute_NeedDealSwipe(HitActor);
		if (bObj3DDealSwipe)
		{
			ITouchInputInterface::Execute_OnInputSwipeStart(HitActor, SwipeAnchor3D);
		}
	}

	PrevSwipeScreenPosition = AnchorPosition;
}

void AStrategyController::OnSwipeUpdate(const FVector2D& ScreenPosition, float DownTime)
{
	AActor* const InputStart = InputStartActor.Get();
	if (InputStart && bObj3DDealSwipe && InputStart->GetClass()->ImplementsInterface(UTouchInputInterface::StaticClass()))
	{
		ULocalPlayer* const MyPlayer = Cast<ULocalPlayer>(Player);
		const FPlane GroundPlane = FPlane(FVector(0, 0, InputStart->GetActorLocation().Z), FVector(0, 0, 1));

		FVector RayOrigin, RayDirection;
		StrategyKitHelpers::DeprojectScreenToWorld(ScreenPosition, MyPlayer, RayOrigin, RayDirection);
		const FVector ScreenPosition3D = StrategyKitHelpers::IntersectRayWithPlane(RayOrigin, RayDirection, GroundPlane);

		ITouchInputInterface::Execute_OnInputSwipeUpdate(InputStart, ScreenPosition3D - SwipeAnchor3D);
	}
	else
	{
		if (GetStrategyCameraComponent() != nullptr)
		{
			GetStrategyCameraComponent()->OnSwipeUpdate(ScreenPosition, DownTime);
		}
	}

	PrevSwipeScreenPosition = ScreenPosition;
}

void AStrategyController::OnSwipeReleased(const FVector2D& ScreenPosition, float DownTime)
{
	AActor* const InputStart = InputStartActor.Get();
	if (InputStart && bObj3DDealSwipe && InputStart->GetClass()->ImplementsInterface(UTouchInputInterface::StaticClass()))
	{
		ULocalPlayer* const MyPlayer = Cast<ULocalPlayer>(this->Player);
		const FPlane GroundPlane = FPlane(FVector(0, 0, InputStart->GetActorLocation().Z), FVector(0, 0, 1));

		FVector RayOrigin, RayDirection;
		StrategyKitHelpers::DeprojectScreenToWorld(ScreenPosition, MyPlayer, RayOrigin, RayDirection);
		const FVector ScreenPosition3D = StrategyKitHelpers::IntersectRayWithPlane(RayOrigin, RayDirection, GroundPlane);

		ITouchInputInterface::Execute_OnInputSwipeReleased(InputStart, ScreenPosition3D - SwipeAnchor3D, DownTime);
	}
	else
	{
		if (GetStrategyCameraComponent() != nullptr)
		{
			GetStrategyCameraComponent()->OnSwipeReleased(ScreenPosition);
		}
	}	
}

void AStrategyController::OnSwipeTwoPointsStarted(const FVector2D& ScreenPosition1, const FVector2D& ScreenPosition2, float DownTime)
{

}

void AStrategyController::OnSwipeTwoPointsUpdate(const FVector2D& ScreenPosition1, const FVector2D& ScreenPosition2, float DownTime)
{

}

void AStrategyController::OnPinchStarted(const FVector2D& AnchorPosition1, const FVector2D& AnchorPosition2, float DownTime)
{
	// Pass the pinch through to the camera component.
	if (GetStrategyCameraComponent() != nullptr)
	{
		GetStrategyCameraComponent()->OnPinchStarted(InputHandler, AnchorPosition1, AnchorPosition2, DownTime);
	}
}

void AStrategyController::OnPinchUpdate(const FVector2D& ScreenPosition1, const FVector2D& ScreenPosition2, float DownTime)
{
	// Pass the pinch through to the camera component.
	if (GetStrategyCameraComponent() != nullptr)
	{
		GetStrategyCameraComponent()->OnPinchUpdate(InputHandler, ScreenPosition1, ScreenPosition2, DownTime);
	}
}

void AStrategyController::ClearSelectedActor()
{
	// attempt to unselect current selection
	AActor* const OldSelection = SelectedActor.Get();
	if (OldSelection && OldSelection->GetClass()->ImplementsInterface(UTouchInputInterface::StaticClass()))
	{
		ITouchInputInterface::Execute_OnSelectionLost(OldSelection, FVector(), nullptr, ETouchInputEnum::VE_Human);
	}
	SelectedActor = nullptr;
}

void AStrategyController::ForceSelecteActor(AActor* NewSelectedActor)
{
	SetSelectedActor(NewSelectedActor, FVector(), ETouchInputEnum::VE_Human);
}

AStrategyPawn* AStrategyController::GetStrategyPawn() const
{
	return Cast<AStrategyPawn>(GetPawn());
}

UStrategyCameraComponent* AStrategyController::GetStrategyCameraComponent() const
{
	UStrategyCameraComponent* CameraComponent = nullptr;
	if (GetStrategyPawn() != nullptr)
	{
		CameraComponent = GetStrategyPawn()->GetCamera();
	}
	return CameraComponent;
}

AActor* AStrategyController::GetFriendlyTarget(const FVector2D& ScreenPoint, FVector& WorldPoint) const
{
	FHitResult Hit;
	if (GetHitResultAtScreenPosition(ScreenPoint, ECC_GameTraceChannel1, true, Hit))
	{
		WorldPoint = Hit.ImpactPoint;
		return Hit.GetActor();
	}

	return nullptr;
}

void AStrategyController::SetSelectedActor(AActor* NewSelectedActor, const FVector& NewPosition, ETouchInputEnum InputType)
{
	if (SelectedActor != NewSelectedActor)
	{
		// attempt to unselect current selection
		AActor* const OldSelection = SelectedActor.Get();
		if (OldSelection && OldSelection->GetClass()->ImplementsInterface(UTouchInputInterface::StaticClass()))
		{
			if (ITouchInputInterface::Execute_OnSelectionLost(OldSelection, NewPosition, NewSelectedActor, InputType))
			{
				SelectedActor = nullptr;
			}
		}

		if (!SelectedActor.IsValid())
		{
			// attempt to select new selection
			if (NewSelectedActor && NewSelectedActor->GetClass()->ImplementsInterface(UTouchInputInterface::StaticClass()))
			{
				if (ITouchInputInterface::Execute_OnSelectionGained(NewSelectedActor, InputType))
				{
					SelectedActor = NewSelectedActor;
				}
			}
		}
	}
}