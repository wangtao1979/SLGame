// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Camera/CameraComponent.h"
#include "StrategyCameraComponent.generated.h"

class AStrategyPawn;


/**
 *
 */
UCLASS(config = Game, BlueprintType, HideCategories = Trigger, meta = (BlueprintSpawnableComponent))
class UStrategyCameraComponent : public UCameraComponent
{
	GENERATED_UCLASS_BODY()

public:

	// Begin UCameraComponent interface

	virtual void GetCameraView(float DeltaTime, FMinimalViewInfo& DesiredView) override;

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	// End UCameraComponent interface

	UPROPERTY(Category = Camera, BlueprintReadWrite, EditAnywhere)
		float SwipeScale;

	UPROPERTY(Category = Camera, BlueprintReadWrite, EditAnywhere)
		float MaxSwipeSpeed;

	/** The pinch scale of the camera. */
	UPROPERTY(Category = Camera, BlueprintReadWrite, EditAnywhere)
		float PinchScale;

	UPROPERTY(Category = Camera, BlueprintReadWrite, EditAnywhere)
		float SpringArmMinLength;

	UPROPERTY(Category = Camera, BlueprintReadWrite, EditAnywhere)
		float SpringArmMaxLength;

	UPROPERTY(Category = Camera, BlueprintReadWrite, EditAnywhere)
		float MaxMoveY;

	UPROPERTY(Category = Camera, BlueprintReadWrite, EditAnywhere)
		float MaxMoveX;

	//UPROPERTY(Category = Camera, BlueprintReadWrite, EditAnywhere)
	
	
	/*
	* Handle the start of a 'pinch'.
	*
	* @param	AnchorPosition1		First Anchor position.
	* @param	AnchorPosition2		Second Anchor position.
	* @param	DownTime			Time pressed.
	*/
	void OnPinchStarted(class UTouchInput* InputHandler, const FVector2D& AnchorPosition1, const FVector2D& AnchorPosition2, float DownTime);

	/** Handle the start of a 'pinch'.
	*
	* @param	InputHandler		The unput handler related to this pinch.
	* @param	AnchorPosition1		First Anchor position.
	* @param	AnchorPosition2		Second Anchor position.
	* @param	DownTime			Time pressed
	*/
	void OnPinchUpdate(class UTouchInput* InputHandler, const FVector2D& ScreenPosition1, const FVector2D& ScreenPosition2, float DownTime);

	/** Set the desired camera position. */
	void SetCameraTarget(FVector& CameraTarget);

	/** Sets the desired zoom level; clamping if necessary */
	void SetZoomLevel(float NewLevel);

	/*
	* Handle the start swipe/drag
	*
	* @param	SwipePosition		Position the swipe begins at
	*
	* @returns	true if the swipe was handled and we begun a swipe/drag
	*/
	bool OnSwipeStarted(const FVector2D& SwipePosition, float DownTime);

	/*
	* Handle the update of a swipe/drag
	*
	* @param	SwipePosition		Position for this update
	* @returns	true if the swipe was handled and we moved the camera position
	*/
	bool OnSwipeUpdate(const FVector2D& SwipePosition, float DownTime);

	/*
	* Handle the start swipe/drag
	*
	* @param	SwipePosition		Position the swipe ends
	* @returns	true if the swipe was handled and we ended the swipe/drag
	*/
	bool OnSwipeReleased(const FVector2D& SwipePosition);

	/* Reset the swipe/drag */
	void EndSwipeNow();

private:

	FVector  GetSwip3DPos(const FVector2D& SwipePosition);

	/** Return the pawn that owns this component. */
	AStrategyPawn* GetOwnerPawn();

	/** Return the player controller of the pawn that owns this component. */
	APlayerController* GetPlayerController();

	//检查是否需要惯性移动
	bool NeedMove();

	//处理惯性移动
	void Moveing(float DeltaTime);

	/** The initial position of the swipe/drag. */
	FVector StaStrategywipeCoords;
	float LastSwipeTime;
	FVector DeltaSpeedDir;
	float DeltaSpeedValue;
	bool NeedMoveMore;
	
	//拉近拉远
	float ZoomAlpha;
	float InitZoomALpha;

	FVector2D InitDir;
	float OldDegress;

	FVector StrartPoint;
};
