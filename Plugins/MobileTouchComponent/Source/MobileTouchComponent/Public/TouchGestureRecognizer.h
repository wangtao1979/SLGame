// =================================================================================================
//
//       ^                     ____________________
//      / \                   |                   |
//     / _ \                  | MartianCraft      |
//    ( (_) )                 | Public Code       |
//   /|  |  |\                |___________________|
//  //|__|__|\\
// (/   (|)   \)
//      \ /
//       v
//
//    Copyright 2015 MartianCraft. All rights reserved.
//    http://www.martiancraft.com       jeff@martiancraft.com
//
//	Permission is hereby granted, free of charge, to any person obtaining a copy
//	of this software and associated documentation files (the "Software"), to deal
//	in the Software without restriction, including without limitation the rights
//	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//	copies of the Software, and to permit persons to whom the Software is
//	furnished to do so, subject to the following conditions:
//
//	The above copyright notice and this permission notice shall be included in
//	all copies or substantial portions of the Software.
//
//	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//	THE SOFTWARE.
//
// =================================================================================================

#pragma once

#include "GestureRecognizerComponent.h"
#include "TouchGestureRecognizer.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FHold, UTouchGestureRecognizer *, Recognizer, FVector2D, StartPostion, FVector2D, EndPostion, float, DeltaTime);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FHoldEnd, UTouchGestureRecognizer *, Recognizer, FVector2D, StartPostion, FVector2D, EndPostion, float, DeltaTime);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDoubleTap, UTouchGestureRecognizer *, Recognizer, FVector2D, Postion);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FTap, UTouchGestureRecognizer *, Recognizer, FVector2D, Postion);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FSWipe, UTouchGestureRecognizer *, Recognizer, FVector2D, StartPostion, FVector2D, EndPostion);

/**
 *  Base class for gesture recognizers that continually update their delegate during the gesture, rather than waiting for the gesture to be finished.
 */

UCLASS(ClassGroup=Input, meta=(BlueprintSpawnableComponent))
class MOBILETOUCHCOMPONENT_API UTouchGestureRecognizer : public UGestureRecognizerComponent
{
	GENERATED_BODY()

	UTouchGestureRecognizer();
public:

	UPROPERTY(BlueprintAssignable, Category = Gestures)
	FSWipe GestureSwipeDelegate;

	UPROPERTY(BlueprintAssignable, Category = Gestures)
	FHoldEnd GestureHoldEndDelegate;

	UPROPERTY(BlueprintAssignable, Category=Gestures)
	FHold GestureHoldDelegate;

	UPROPERTY(BlueprintAssignable, Category = Gestures)
	FTap GestureTapDelegate;

	UPROPERTY(BlueprintAssignable, Category = Gestures)
	FDoubleTap GestureDoubleTapDelegate;


	UPROPERTY(EditAnywhere, Category = Gestures)
	float TimeForHold;

	UPROPERTY(EditAnywhere, Category = Gestures)
	float MaxTimeForDoubleTap;

	UPROPERTY(EditAnywhere, Category = Gestures)
	float DistanceForSwipe;
public:
	/** Called when a finger touches down for the first time during a gesture */
	virtual void TouchBegan(int32 FingerIndex, FGestureTouchData& Data);

	/** Called while a finger is touching the screen */
	virtual void TouchMoved(int32 FingerIndex, FGestureTouchData& Data, float DeltaTime);

	/** Called when a finger is lifted from the screen */
	virtual void TouchEnded(int32 FingerIndex, FGestureTouchData& data, float DeltaTime);

	/** Called when a finger is lifted from the screen */
	virtual void TouchHold(int32 FingerIndex, FGestureTouchData& data, float DeltaTime);

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

private:
	int32 TapCounts[EKeys::NUM_TOUCH_KEYS];
};
