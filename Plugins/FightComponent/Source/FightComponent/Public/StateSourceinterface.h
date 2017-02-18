// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "StateSourceInterface.generated.h"

/** Interface for actors which can be selected */
UINTERFACE(Blueprintable)
class FIGHTCOMPONENT_API UStateSourceInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class IStateSourceInterface
{
	GENERATED_IINTERFACE_BODY()

public:

	UFUNCTION(BlueprintNativeEvent)
	void GetState(TArray<uint8> & StateList);


	UFUNCTION(BlueprintNativeEvent)
	bool IsActive();
};
