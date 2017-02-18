// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "FightDef.h"
#include "AttributeSourceInterface.generated.h"

/** Interface for actors which can be selected */
UINTERFACE(Blueprintable)
class FIGHTCOMPONENT_API UAttributeSourceInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class IAttributeSourceInterface
{
	GENERATED_IINTERFACE_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
	bool IsActive();

	UFUNCTION(BlueprintNativeEvent)
	void GetBuffAttribute(TArray<FAttributeBuff> & BuffList);


	UFUNCTION(BlueprintNativeEvent)
	uint8 GetBuffLevel();
};
