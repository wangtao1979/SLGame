// 2014 MartianCraft, LLC, See eader file for license & copyright notice

#include "MobileTouchComponentPrivatePCH.h"
#include "InstantTapRecognizer.h"



void UInstantTapRecognizer::TouchBegan(int32 FingerIndex, FGestureTouchData& Data)
{
	WhichFinger = FingerIndex;
	TouchLocation = Data.TouchPoints.Last();
	GestureStartedDelegate.Broadcast(this, GetWorld()->GetDeltaSeconds());
}

void UInstantTapRecognizer::TouchEnded(int32 FingerIndex, FGestureTouchData& Data, float DeltaTime)
{
	WhichFinger = FingerIndex;
	TouchLocation = TouchData[FingerIndex].TouchPoints.Last();
	GestureEndedDelegate.Broadcast(this, GetWorld()->GetDeltaSeconds());
}