// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "StrategyController.generated.h"

class AStrategyPawn;
class UStrategyCameraComponent;
enum class ETouchInputEnum;

/**
*
*/
UCLASS()
class AStrategyController : public APlayerController
{
	GENERATED_UCLASS_BODY()

protected:
	/** update input detection */
	//virtual bool InputTouch(uint32 Handle, ETouchType::Type Type, const FVector2D& TouchLocation, FDateTime DeviceTimestamp, uint32 TouchpadIndex) override;
	virtual void ProcessPlayerInput(const float DeltaTime, const bool bGamePaused) override;
	virtual void SetupInputComponent() override;

	/** Custom input handler. */
	UPROPERTY()
	class UTouchInput* InputHandler;

	/** if set, input and camera updates will be ignored */
	uint8 bIgnoreInput : 1;

	FVector2D PrevSwipeScreenPosition;

public:

	/** Input handlers. */
	void OnTapPressed(const FVector2D& ScreenPosition, float DownTime);
	void OnHoldPressed(const FVector2D& ScreenPosition, float DownTime);
	void OnHoldReleased(const FVector2D& ScreenPosition, float DownTime);
	void OnSwipeStarted(const FVector2D& AnchorPosition, float DownTime);
	void OnSwipeUpdate(const FVector2D& ScreenPosition, float DownTime);
	void OnSwipeReleased(const FVector2D& ScreenPosition, float DownTime);
	void OnSwipeTwoPointsStarted(const FVector2D& ScreenPosition1, const FVector2D& ScreenPosition2, float DownTime);
	void OnSwipeTwoPointsUpdate(const FVector2D& ScreenPosition1, const FVector2D& ScreenPosition2, float DownTime);
	void OnPinchStarted(const FVector2D& AnchorPosition1, const FVector2D& AnchorPosition2, float DownTime);
	void OnPinchUpdate(const FVector2D& ScreenPosition1, const FVector2D& ScreenPosition2, float DownTime);

public:
	UFUNCTION(BlueprintCallable, Category = "StrategyController")
	void ClearSelectedActor();

	UFUNCTION(BlueprintCallable, Category = "StrategyController")
	void ForceSelecteActor(AActor* NewSelectedActor);
private:
	/** Helper to return cast version of Spectator pawn. */
	AStrategyPawn* GetStrategyPawn() const;

	/** Helper to return camera component via spectator pawn. */
	UStrategyCameraComponent* GetStrategyCameraComponent() const;

	/**
	* Get friendly target under screen space coordinates.
	*
	* @param	ScreenPoint	Screen coordinates to check
	* @param	WorldPoint	Point in the world the screen coordinates projected onto.
	*/
	AActor* GetFriendlyTarget(const FVector2D& ScreenPoint, FVector& WorldPoint) const;


	/**
	* Change current selection (on toggle on the same).
	*
	* @param	NewFocus	Actor to focus on.
	* @param	NewPosition
	*/
	void SetSelectedActor(AActor* NewFocus, const FVector& NewPosition, ETouchInputEnum InputType);

	/** currently selected actor */
	TWeakObjectPtr<AActor> SelectedActor;

	TWeakObjectPtr<AActor> InputStartActor;

	/** Swipe anchor. */
	FVector SwipeAnchor3D;

	bool bObj3DDealSwipe;
};
