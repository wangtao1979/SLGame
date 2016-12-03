// 2014 MartianCraft, LLC, See eader file for license & copyright notice

#include "MobileTouchComponentPrivatePCH.h"
#include "TouchGestureRecognizer.h"

UTouchGestureRecognizer::UTouchGestureRecognizer() : Super()
, TimeForHold(0.5)
, MaxTimeForDoubleTap(0.3)
, DistanceForSwipe(30)
{
	bFlushTouchDataOnGestureEnded = false;
}


void UTouchGestureRecognizer::TouchBegan(int32 FingerIndex, FGestureTouchData& Data)
{
	//UE_LOG(LogTemp, Warning, TEXT("TouchBegan"));
}

void UTouchGestureRecognizer::TouchMoved(int32 FingerIndex, FGestureTouchData& Data, float DeltaTime)
{
	//UE_LOG(LogTemp, Warning, TEXT("TouchMoved"));
	//UE_LOG(LogTemp, Warning, TEXT("DeltaTime=%f TimeForHold=%f"), DeltaTime, TimeForHold);
	if (DeltaTime >= TimeForHold)
	{
		GestureHoldDelegate.Broadcast(this, Data.TouchPoints[0], GetTouchLocation(FingerIndex), DeltaTime);
	}
}

void UTouchGestureRecognizer::TouchHold(int32 FingerIndex, FGestureTouchData& Data, float DeltaTime)
{
	if (DeltaTime >= TimeForHold)
	{
		//UE_LOG(LogTemp, Warning, TEXT("TouchHold"));
		GestureHoldDelegate.Broadcast(this, Data.TouchPoints[0], GetTouchLocation(FingerIndex), DeltaTime);
	}
}

void UTouchGestureRecognizer::TouchEnded(int32 FingerIndex, FGestureTouchData& Data, float DeltaTime)
{
	//UE_LOG(LogTemp, Warning, TEXT("TouchEnded"));
	if (DeltaTime < TimeForHold) 
	{
		if (Data.TouchPoints.Num() > 1 && Data.GestureLength() > DistanceForSwipe)
		{
			GestureSwipeDelegate.Broadcast(this, Data.TouchPoints[0], Data.TouchPoints.Last());
			ResetGesture();
		}else if (Data.TouchEndTimes.Num() > 1)
		{
			if (Data.TouchEndTimes.Last() - Data.TouchEndTimes.Last(1)<MaxTimeForDoubleTap)
			{
				GestureDoubleTapDelegate.Broadcast(this, Data.TouchPoints.Last());
				ResetGesture();
			}
		}
		else
		{
			GestureTapDelegate.Broadcast(this, Data.TouchPoints.Last());
		}
	}
	else
	{
		GestureHoldEndDelegate.Broadcast(this, Data.TouchPoints[0], Data.TouchPoints.Last(), DeltaTime);
		ResetGesture();
	}
}

void UTouchGestureRecognizer::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (MaxFingersThisGesture>0 && GetWorld()->GetRealTimeSeconds() - LastFingerTouchTime > MaxTimeForDoubleTap)
	{
		ResetGesture();
	}
}