// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CreatureAttributeBuffRule.h"
#include "CreatureAttributeRule.h"
#include "FightConfigerInterface.generated.h"

/** Interface for actors which can be selected */
UINTERFACE(Blueprintable)
class FIGHTCOMPONENT_API UFightConfigerInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class IFightConfigerInterface
{
	GENERATED_IINTERFACE_BODY()

public:

	UFUNCTION(BlueprintNativeEvent)
	UCreatureAttributeRule* GetAttributeRule();


	UFUNCTION(BlueprintNativeEvent)
	UCreatureAttributeBuffRule* GetAttributeBuffRule();
};
