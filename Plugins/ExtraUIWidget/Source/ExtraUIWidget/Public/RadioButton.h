// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Components/ContentWidget.h"
#include "Slate/SlateBrushAsset.h"
#include "Components/CheckBox.h"
#include "RadioButton.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FRadioButtonClick, URadioButton *, Button, int32, RadioIndex);

UCLASS()
class EXTRAUIWIDGET_API URadioButton : public UCheckBox
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = "RadioButton")
	int32 RadioIndex;

	UPROPERTY(BlueprintAssignable, Category = "RadioButton|Event")
	FRadioButtonClick OnRadioClicked;

	UFUNCTION()
	void OnRadioCheckStateChanged(bool State);
};