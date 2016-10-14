// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "StrategyKitPrivatePCH.h"
#include "StrategyCameraComponent.h"
#include "StrategyPawn.h"
#include "TouchInput.h"
#include "StrategyKitHelpers.h"

UStrategyCameraComponent::UStrategyCameraComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SwipeScale = 50000.0f;
	MaxSwipeSpeed = 20000.0f;
	PinchScale = 0.002f;
	StaStrategywipeCoords.Set(0.0f, 0.0f, 0.0f);
	LastSwipeTime = 0.0f;
	DeltaSpeedDir.Set(0.0f, 0.0f, 0.0f);
	DeltaSpeedValue = 0.0f;
	NeedMoveMore = 0.0f;
	SpringArmMinLength = 500.0f;
	SpringArmMaxLength = 2000.0f;
	MaxMoveX = 2000;
	MaxMoveY = 2000;
	PrimaryComponentTick.bCanEverTick = true;
}

void UStrategyCameraComponent::GetCameraView(float DeltaTime, FMinimalViewInfo& OutResult)
{
	Super::GetCameraView(DeltaTime, OutResult);
}

void UStrategyCameraComponent::BeginPlay()
{
	Super::BeginPlay();
	auto sprintArm = GetOwnerPawn()->GetSpringArm();
	auto CurrentCameraZoomDistance = sprintArm->TargetArmLength;
	CurrentCameraZoomDistance = FMath::Clamp(CurrentCameraZoomDistance, SpringArmMinLength, SpringArmMaxLength);
	sprintArm->TargetArmLength = CurrentCameraZoomDistance;
	ZoomAlpha = (CurrentCameraZoomDistance - SpringArmMinLength) / (SpringArmMaxLength - SpringArmMinLength);

	StrartPoint = GetOwnerPawn()->GetActorLocation();
}

void UStrategyCameraComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (NeedMove())
	{
		Moveing(DeltaTime);
	}
}

AStrategyPawn* UStrategyCameraComponent::GetOwnerPawn()
{
	return Cast<AStrategyPawn>(GetOwner());
}

APlayerController* UStrategyCameraComponent::GetPlayerController()
{
	APlayerController* Controller = NULL;
	AStrategyPawn* Owner = GetOwnerPawn();
	if (Owner != NULL)
	{
		Controller = Cast<APlayerController>(Owner->GetController());
	}
	return Controller;
}

bool UStrategyCameraComponent::NeedMove()
{
	return NeedMoveMore && (DeltaSpeedValue > 0.000001f);
}

void UStrategyCameraComponent::Moveing(float DeltaTime)
{
	FVector CurrentCamera = GetOwnerPawn()->GetActorLocation();
	CurrentCamera += (DeltaSpeedValue * DeltaTime - SwipeScale * DeltaTime * DeltaTime/2) * DeltaSpeedDir;
	SetCameraTarget(CurrentCamera);
	DeltaSpeedValue -= SwipeScale * DeltaTime;	
}

void UStrategyCameraComponent::OnPinchStarted(UTouchInput* InputHandler, const FVector2D& AnchorPosition1, const FVector2D& AnchorPosition2, float DownTime)
{
	InitZoomALpha = ZoomAlpha;

	FVector2D old1 = InputHandler->GetTouchAnchor(0);
	FVector2D old2 = InputHandler->GetTouchAnchor(1);
	InitDir = old2 - old1;
	InitDir.Normalize();
}

void UStrategyCameraComponent::OnPinchUpdate(UTouchInput* InputHandler, const FVector2D& ScreenPosition1, const FVector2D& ScreenPosition2, float DownTime)
{
	FVector2D old1 = InputHandler->GetTouchAnchor(0);
	FVector2D old2 = InputHandler->GetTouchAnchor(1);
	const float AnchorDistance = (old1 - old2).Size();
	const float CurrentDistance = (ScreenPosition1 - ScreenPosition2).Size();
	const float PinchDelta = AnchorDistance - CurrentDistance;

	//FVector2D dir1 = old2 - old1;
	//dir1.Normalize();
	FVector2D dir2 = ScreenPosition2 - ScreenPosition1;
	dir2.Normalize();

	float radians = FGenericPlatformMath::Acos(FVector2D::DotProduct(InitDir, dir2));
	auto degress = FMath::RadiansToDegrees(radians);
	float tempDir = FGenericPlatformMath::Asin(FVector2D::CrossProduct(InitDir, dir2));
	degress = tempDir > 0.f ? -degress : degress;
	GetOwnerPawn()->AddControllerYawInput(degress);
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("OnPinchUpdate degress %f"), degress));

	//tempRotator = GetOwnerPawn()->GetActorRotation();
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("OnPinchUpdate after rotate %f %f %f"), tempRotator.Pitch, tempRotator.Roll, tempRotator.Yaw));
	InitDir = dir2;

	SetZoomLevel(PinchDelta * PinchScale);
}

void UStrategyCameraComponent::SetCameraTarget(FVector& CameraTarget)
{
	if (CameraTarget.X - StrartPoint.X > MaxMoveX)
	{
		CameraTarget.X = StrartPoint.X + MaxMoveX;
	}
	else if (CameraTarget.X - StrartPoint.X < -MaxMoveX)
	{
		CameraTarget.X = StrartPoint.X - MaxMoveX;
	}

	if (CameraTarget.Y - StrartPoint.Y > MaxMoveY)
	{
		CameraTarget.Y = StrartPoint.Y + MaxMoveY;
	}
	else if (CameraTarget.Y - StrartPoint.Y < -MaxMoveY)
	{
		CameraTarget.Y = StrartPoint.Y - MaxMoveY;
	}
	GetOwnerPawn()->SetActorLocation(CameraTarget, false);
}

void UStrategyCameraComponent::SetZoomLevel(float NewLevel)
{
	ZoomAlpha = FMath::Clamp(NewLevel + InitZoomALpha, 0.0f, 1.0f);	

	auto sprintArm = GetOwnerPawn()->GetSpringArm();
	float TargetArmDistance = ZoomAlpha*(SpringArmMaxLength - SpringArmMinLength) + SpringArmMinLength;
	sprintArm->TargetArmLength = TargetArmDistance;
}

FVector  UStrategyCameraComponent::GetSwip3DPos(const FVector2D& SwipePosition)
{
	APlayerController* Controller = GetPlayerController();
	AStrategyPawn* Pawn = GetOwnerPawn();

	ULocalPlayer* const MyPlayer = Controller->GetLocalPlayer();
	const FPlane GroundPlane = FPlane(FVector(0, 0, Pawn->GetActorLocation().Z), FVector(0, 0, 1));

	FVector RayOrigin, RayDirection;
	StrategyKitHelpers::DeprojectScreenToWorld(SwipePosition, MyPlayer, RayOrigin, RayDirection);
	return StrategyKitHelpers::IntersectRayWithPlane(RayOrigin, RayDirection, GroundPlane);
}


bool UStrategyCameraComponent::OnSwipeStarted(const FVector2D& SwipePosition, float DownTime)
{	
	NeedMoveMore = false;
	LastSwipeTime = DownTime;
	APlayerController* Controller = GetPlayerController();
	if (Controller)
	{
		StaStrategywipeCoords = GetSwip3DPos(SwipePosition);		
	}
	return true;
}

bool UStrategyCameraComponent::OnSwipeUpdate(const FVector2D& SwipePosition, float DownTime)
{
	bool bResult = false;
	float DeltaTime = DownTime - LastSwipeTime;
	APlayerController* Controller = GetPlayerController();
	if ((Controller != NULL) && (StaStrategywipeCoords.IsNearlyZero() == false))
	{
		FVector NewSwipeCoords = GetSwip3DPos(SwipePosition);
		FVector Delta = StaStrategywipeCoords - NewSwipeCoords;
		// Flatten Z axis - we are not interested in that.
		Delta.Z = 0.0f;
		if (Delta.IsNearlyZero() == false)
		{
			FVector CurrentCamera = GetOwnerPawn()->GetActorLocation();
			CurrentCamera += Delta;
			DeltaSpeedValue = Delta.Size()/ DeltaTime;
			DeltaSpeedDir = Delta;
			SetCameraTarget(CurrentCamera);
			bResult = true;
		}		
	}
	LastSwipeTime = DownTime;
	return bResult;
}

bool UStrategyCameraComponent::OnSwipeReleased(const FVector2D& SwipePosition)
{
	DeltaSpeedValue = FMath::Clamp(DeltaSpeedValue, 0.0f, MaxSwipeSpeed);
	NeedMoveMore = true;
	DeltaSpeedDir.Normalize();
	LastSwipeTime = 0.0f;
	bool bResult = false;
	if (StaStrategywipeCoords.IsNearlyZero() == false)
	{
		EndSwipeNow();
	}
	return false;
}

void UStrategyCameraComponent::EndSwipeNow()
{
	StaStrategywipeCoords.Set(0.0f, 0.0f, 0.0f);
}
