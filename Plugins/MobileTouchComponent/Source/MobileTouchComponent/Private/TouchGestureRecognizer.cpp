// 2014 MartianCraft, LLC, See eader file for license & copyright notice

#include "MobileTouchComponentPrivatePCH.h"
#include "TouchGestureRecognizer.h"

UTouchGestureRecognizer::UTouchGestureRecognizer() : Super()
, TimeForHold(0.5)
, MaxTimeForDoubleTap(0.3)
, DistanceForSwipe(30)
, SwipTime(0)
, SwipRecordNumber(1)
{
	bFlushTouchDataOnGestureEnded = false;
}

bool UTouchGestureRecognizer::IsHolding(int32 FingerIndex, FGestureTouchData& Data, float DeltaTime)
{
	if (Data.TouchStartTimes.Num() > 1)
	{
		return Data.TouchStartTimes[1]- Data.TouchStartTimes[0] > TimeForHold;
	}
	else
	{
		return DeltaTime > TimeForHold;
	}
}

bool UTouchGestureRecognizer::IsSingleSwipe(int32 FingerIndex, FGestureTouchData& Data, float DeltaTime)
{
	if (Data.TouchPoints.Num() > 2 )
	{
		FVector2D TouchDelta = Data.TouchPoints.Last(2) - Data.TouchPoints.Last();
		TouchDelta = UGestureMathLibrary::ScaleVector2DForScreen(TouchDelta);
		float MovementSquared = TouchDelta.SizeSquared();
		return MovementSquared > ToleranceSquared;
	}

	return false;
}

void UTouchGestureRecognizer::TouchBegan(int32 FingerIndex, FGestureTouchData& Data)
{
	//UE_LOG(LogTemp, Warning, TEXT("TouchBegan"));
}

void UTouchGestureRecognizer::TouchMoved(int32 FingerIndex, FGestureTouchData& Data, float DeltaTime)
{
	if (IsHolding(FingerIndex,Data,DeltaTime))
	{
		GestureHoldDelegate.Broadcast(this, Data.TouchPoints[0], GetTouchLocation(FingerIndex), DeltaTime);
	}
	else if(Data.TouchPoints.Num() > SwipRecordNumber)
	{
		SwipRecordNumber = Data.TouchPoints.Num();
		GestureSwipeDelegate.Broadcast(this, Data.TouchPoints.Last(1), Data.TouchPoints.Last(), ++SwipTime,false);
	}
}

void UTouchGestureRecognizer::TouchHold(int32 FingerIndex, FGestureTouchData& Data, float DeltaTime)
{
	if (IsHolding(FingerIndex, Data, DeltaTime))
	{
		//UE_LOG(LogTemp, Warning, TEXT("TouchHold"));
		GestureHoldDelegate.Broadcast(this, Data.TouchPoints[0], GetTouchLocation(FingerIndex), DeltaTime);
	}
}

void UTouchGestureRecognizer::TouchEnded(int32 FingerIndex, FGestureTouchData& Data, float DeltaTime)
{
	//UE_LOG(LogTemp, Warning, TEXT("TouchEnded DeltaTime=%f MaxTimeForDoubleTap=%f TimeForHold=%f touh number=%d"), DeltaTime, MaxTimeForDoubleTap, TimeForHold, Data.TouchEndTimes.Num());
	SwipTime = 0;
	SwipRecordNumber = 1;
	if (IsHolding(FingerIndex, Data, DeltaTime))
	{
		GestureHoldEndDelegate.Broadcast(this, Data.TouchPoints[0], Data.TouchPoints.Last(), DeltaTime);
		ResetGesture();
	}
	else
	{
		if (IsSingleSwipe(FingerIndex, Data, DeltaTime))
		{
			GestureSwipeDelegate.Broadcast(this, Data.TouchPoints.Last(2), Data.TouchPoints.Last(0), SwipTime, true);
			ResetGesture();
		}
		else if (Data.TouchEndTimes.Num() > 1)
		{
			if (DeltaTime < MaxTimeForDoubleTap)
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
}

void UTouchGestureRecognizer::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (MaxFingersThisGesture>0 && GetWorld()->GetRealTimeSeconds() - LastFingerTouchTime > MaxTimeForDoubleTap)
	{
		ResetGesture();
	}
}

void UTouchGestureRecognizer::InitializeComponent()
{
	MoveTolerance = DistanceForSwipe;
	ToleranceSquared = MoveTolerance * MoveTolerance;
}