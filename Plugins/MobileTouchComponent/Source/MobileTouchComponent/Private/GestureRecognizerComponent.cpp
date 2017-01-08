// 2014 MartianCraft, LLC, See eader file for license & copyright notice

#include "MobileTouchComponentPrivatePCH.h"
#include "GestureRecognizerComponent.h"


// Sets default values for this component's properties
UGestureRecognizerComponent::UGestureRecognizerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsInitializeComponent = true;
	PrimaryComponentTick.bCanEverTick = true;
	DelayBeforeResetting = 0.f;
	bFlushTouchDataOnGestureEnded = true;

	MoveTolerance = 15;
	SamplIdle = 0.02f;
	//PrimaryComponentTick.TickInterval = SamplIdle;
}

// Called when the game starts
void UGestureRecognizerComponent::InitializeComponent()
{
	Super::InitializeComponent();
	ResetGesture();
	
	AActor *Owner = GetOwner();
	if (Owner->IsValidLowLevel())
	{
		AddTickPrerequisiteActor(Owner);
	}
	
	APlayerController *Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (Controller->IsValidLowLevel())
	{
		PlayerInput = Controller->PlayerInput;
	}

	ToleranceSquared = MoveTolerance * MoveTolerance;
}

void UGestureRecognizerComponent::ProcessTouches(const FVector (&Touches)[EKeys::NUM_TOUCH_KEYS], float DeltaTime)
{
	CalculateTouchCount(Touches);
	
	UpdateStoredTouchData(Touches);
	
	// If no touches, return immediately to avoid unnecessary processing
	if (CurrentTouchCount == 0)
	{
		if (PreviousTouchCount > 0)
		{
			// Final processing, then reset touch data. Subclasses that detect gestures like double-taps will should set a non-zero reset delay so they have access to touch data
			GestureFinished(DeltaTime);
			
			if (bFlushTouchDataOnGestureEnded)
			{
				if (DelayBeforeResetting == 0.f)
				{
					ResetGesture();
				}
				else
				{
					FTimerHandle Handle;
					GetWorld()->GetTimerManager().SetTimer(Handle, this, &UGestureRecognizerComponent::ResetGesture, DelayBeforeResetting, false);
				}
			}
		}
		return;
	}
}

void UGestureRecognizerComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{

	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (!PlayerInput->IsValidLowLevel())
	{
		// If not valid, try again to get it.
		
		
		APlayerController *Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		if (Controller->IsValidLowLevel())
		{
			PlayerInput = Controller->PlayerInput;
		}
		
		// If still not valid, return
		if (!PlayerInput->IsValidLowLevel())
			return;
	}
	ProcessTouches(PlayerInput->Touches, DeltaTime);
	DetectGestures(DeltaTime);
	PreviousTouchCount = CurrentTouchCount;
}

// ===========================================================================
// Detection Methods for subclasses to override

void UGestureRecognizerComponent::DetectGestures(float DeltaTime)
{
	
}

void UGestureRecognizerComponent::GestureFinished(float DeltaTime)
{
	
}

void UGestureRecognizerComponent::TouchBegan(int32 FingerIndex, FGestureTouchData& Data)
{
	
}

void UGestureRecognizerComponent::TouchMoved(int32 FingerIndex, FGestureTouchData& Data, float DeltaTime)
{
	
}

void UGestureRecognizerComponent::TouchHold(int32 FingerIndex, FGestureTouchData& Data, float DeltaTime)
{

}


void UGestureRecognizerComponent::TouchEnded(int32 FingerIndex, FGestureTouchData& Data, float DeltaTime)
{
	
}

FVector2D UGestureRecognizerComponent::GetTouchLocation(int32 FingerIndex) const
{
	check(FingerIndex < EKeys::NUM_TOUCH_KEYS);
	return FVector2D(PlayerInput->Touches[FingerIndex].X, PlayerInput->Touches[FingerIndex].Y);
}
// ===========================================================================
// Protected Methods

void UGestureRecognizerComponent::ResetGesture()
{
	//UE_LOG(LogTemp, Warning, TEXT("ResetGesture"));
	CurrentTouchCount = PreviousTouchCount = MaxFingersThisGesture = 0;
	for (int32 Index = 0; Index < ARRAY_COUNT(TouchData); Index++)
	{
		TouchData[Index].TouchPoints.Empty();
		TouchData[Index].FirstTouchTime = 0;
		TouchData[Index].LatestTouchTime = 0;
		TouchData[Index].bIsTouched = false;
		TouchData[Index].TouchStartTimes.Empty();
		TouchData[Index].TouchEndTimes.Empty();
		bWasDownPreviously[Index] = false;
	}
	
}

// Store the touches in easy to process format
void UGestureRecognizerComponent::UpdateStoredTouchData(const FVector (&Touches)[EKeys::NUM_TOUCH_KEYS])
{
	// No touches this or last frame, nothing to do, so skip out early
	if (CurrentTouchCount == 0 && PreviousTouchCount == 0) return;
	
	float now = GetWorld()->GetRealTimeSeconds(); // Real time, not game time, because should work on pause or time dilation
	
	if (CurrentTouchCount > 0 && PreviousTouchCount == 0)
	{
		FirstFingerTouchTime = now;
	}

	for (int32 Index = 0; Index < ARRAY_COUNT(TouchData); Index++)
	{
		FVector2D Postion = FVector2D(Touches[Index].X, Touches[Index].Y);
		FGestureTouchData& ThisTouch = TouchData[Index];
		// If it's a touch, store the position of the touch
		if (Index < CurrentTouchCount)
		{
			if (!bWasDownPreviously[Index])
			{
				ThisTouch.SampleTouch(Postion, now);
				TouchBegan(Index, ThisTouch);
				bWasDownPreviously[Index] = true;
			}
			else
			{

				// check is touch move
				FVector2D TouchDelta = Postion - ThisTouch.TouchPoints.Last();
				TouchDelta = UGestureMathLibrary::ScaleVector2DForScreen(TouchDelta);
				float MovementSquared = TouchDelta.SizeSquared();

				if (MovementSquared > ToleranceSquared) //
				{
					ThisTouch.SampleTouch(Postion, now);
				}
				//UE_LOG(LogTemp, Warning, TEXT("MovementSquared=%f"), MovementSquared);
				if(MovementSquared>10.0f)
				{
					TouchMoved(Index, ThisTouch, now - ThisTouch.TouchStartTimes[0]);
				}
				else
				{
					TouchHold(Index, ThisTouch, now - ThisTouch.TouchStartTimes.Last());
				}
			}
		}
		// Not a touch, mark it as ended.
		else
		{
			if (bWasDownPreviously[Index])
			{
				ThisTouch.SampleTouch(Postion, now);
				ThisTouch.EndTouch(now);
				TouchEnded(Index, ThisTouch, now - ThisTouch.FirstTouchTime);
				bWasDownPreviously[Index] = false;
			}
		}
	}
	LastFingerTouchTime = now;
}

void UGestureRecognizerComponent::CalculateTouchCount(const FVector (&Touches)[EKeys::NUM_TOUCH_KEYS])
{
	int32 TouchCount = 0;
	for (int32 TouchIndex = 0; TouchIndex < EKeys::NUM_TOUCH_KEYS; TouchIndex++)
	{
		if (Touches[TouchIndex].Z != 0)
		{
			TouchCount++;
		}
	}
	CurrentTouchCount = TouchCount;
	if (CurrentTouchCount > MaxFingersThisGesture)
	{
		MaxFingersThisGesture = CurrentTouchCount;
	}
}


bool UGestureRecognizerComponent::GetImpactGroundPoint(APlayerController * controller,TEnumAsByte<ECollisionChannel> TraceChannel, FVector2D ScreenSPoint, FVector& ImpactPoint)
{
	// Trace to see what is under the touch location
	FHitResult HitResult;
	//this->SetViewTargetWithBlend()
	controller->GetHitResultAtScreenPosition(ScreenSPoint, TraceChannel, true, HitResult);
	if (HitResult.bBlockingHit)
	{
		ImpactPoint = HitResult.ImpactPoint;
		return true;
	}
	return false;
}