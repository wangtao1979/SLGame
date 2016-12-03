#pragma once

#include "Object.h"
#include "StateSourceinterface.h"
#include "CreatureAttributeBuffRule.generated.h"

/**
*
*/
UCLASS(BlueprintType, Blueprintable)
class UCreatureAttributeBuffRule : public UObject
{
	GENERATED_BODY()
protected:

public:

	UFUNCTION(BlueprintImplementableEvent, Category = "CreatureAttribute")
	void InitRule();

	UFUNCTION(BlueprintImplementableEvent, Category = "CreatureAttribute")
	int GetBuffLevel();
};