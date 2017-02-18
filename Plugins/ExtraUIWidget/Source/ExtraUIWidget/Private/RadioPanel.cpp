
// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "ExtraUIWidgetPrivatePCH.h"
#include "RadioPanel.h"

void URadioPanel::OnButtonPressed(URadioButton * PressedButton, int32 RadioIndex)
{

	for (URadioButton* button : ButtonList)
	{
		if (button != PressedButton)
		{
			button->SetCheckedState(ECheckBoxState::Unchecked);
		}
	}
	PressedButton->SetCheckedState(ECheckBoxState::Checked);
	OnClicked.Broadcast(PressedButton, RadioIndex);
}


void URadioPanel::OnWidgetRebuilt()
{
	for (int32 SlotIndex = 0; SlotIndex < Slots.Num(); SlotIndex++)
	{
		URadioButton* CheckBox = Cast<URadioButton>(Slots[SlotIndex]->Content);
		if (CheckBox != nullptr)
		{
			int32 Index = GetChildIndex(CheckBox);
			CheckBox->RadioIndex = Index;

			CheckBox->OnCheckStateChanged.AddDynamic(CheckBox, &URadioButton::OnRadioCheckStateChanged);
			CheckBox->OnRadioClicked.AddDynamic(this, &URadioPanel::OnButtonPressed);
		}
	}
}
