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
#include "DynamicGestureRecognizer.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGestureMoved, UGestureRecognizerComponent *, Recognizer, float, DeltaTime);

/**
 *  Base class for gesture recognizers that continually update their delegate during the gesture, rather than waiting for the gesture to be finished.
 */

UCLASS(ClassGroup=Input, meta=(BlueprintSpawnableComponent))
class  UDynamicGestureRecognizer : public UGestureRecognizerComponent
{
	GENERATED_BODY()
	
public:
	/** Delegate function called for ongoing gestures. This value is used, for example, to repeatedly provide the current values of a pinch or rotate gesture */
	UPROPERTY(BlueprintAssignable, Category=Gestures)
	FGestureMoved GestureMovedDelegate;
	
};
