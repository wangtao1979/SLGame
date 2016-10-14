// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "TouchInputInterface.generated.h"

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class ETouchInputEnum
{
	VE_Tap 	UMETA(DisplayName = "Tap"),
	VE_Hold 	UMETA(DisplayName = "Hold"),
	VE_Swipe	UMETA(DisplayName = "Swipe"),
	VE_Human	UMETA(DisplayName = "Human")
};

/** Interface for actors which can be selected */
UINTERFACE(Blueprintable)
class UTouchInputInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class ITouchInputInterface
{
	GENERATED_IINTERFACE_BODY()

public:

	/** receive input: tap */
	UFUNCTION(BlueprintImplementableEvent)
	bool OnInputTap();

	/** receive input: hold */
	UFUNCTION(BlueprintImplementableEvent)
	bool OnInputHold();

	/** receive input: hold released */
	UFUNCTION(BlueprintImplementableEvent)
	bool OnInputHoldReleased(float DownTime);

	/** receive input: swipe update (world space, not screen space)*/
	UFUNCTION(BlueprintImplementableEvent)
	bool OnInputSwipeStart(const FVector& StartPosition);

	/** receive input: swipe update (world space, not screen space)*/
	UFUNCTION(BlueprintImplementableEvent)
	bool OnInputSwipeUpdate(const FVector& DeltaPosition);

	/** receive input: swipe finished (world space, not screen space) */
	UFUNCTION(BlueprintImplementableEvent)
	bool OnInputSwipeReleased(const FVector& DeltaPosition, float DownTime);

	/** tries to select actor */
	UFUNCTION(BlueprintImplementableEvent)
	bool OnSelectionGained(ETouchInputEnum InputType);

	/** tries to deselect actor */
	UFUNCTION(BlueprintImplementableEvent)
	bool OnSelectionLost(const FVector& NewPosition, AActor* NewActor, ETouchInputEnum InputType);

	/** tries to select actor */
	UFUNCTION(BlueprintImplementableEvent)
	bool NeedDealSwipe();
};
