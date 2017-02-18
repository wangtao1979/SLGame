// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Components/CanvasPanel.h"
#include "Components/PanelSlot.h"
#include "RadioButton.h"
#include "RadioPanel.generated.h"


DECLARE_DYNAMIC_DELEGATE_TwoParams(FRadioPanelClick, URadioButton *, Button, int32, RadioIndex);

/**
* An arbitrary scrollable collection of widgets.  Great for presenting 10-100 widgets in a list.  Doesn't support virtualization.
*/
UCLASS()
class EXTRAUIWIDGET_API URadioPanel : public UCanvasPanel
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TArray<URadioButton*> ButtonList;

	UPROPERTY(BlueprintAssignable, Category = "RadioButton|Event")
	FRadioButtonClick OnClicked;

	UPROPERTY()
	FRadioPanelClick OnRadioClicked;

	virtual void OnWidgetRebuilt() override;

	UFUNCTION()
	void OnButtonPressed(URadioButton * PressedButton, int32 RadioIndex);
};
