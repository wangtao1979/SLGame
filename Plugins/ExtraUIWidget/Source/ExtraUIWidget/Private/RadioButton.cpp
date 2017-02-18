
// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "ExtraUIWidgetPrivatePCH.h"
#include "RadioButton.h"


void URadioButton::OnRadioCheckStateChanged(bool State)
{
	OnRadioClicked.Broadcast(this, RadioIndex);
}
