#pragma once

#include "Object.h"
#include "StateSourceinterface.h"
#include "CreatureStateContainer.generated.h"

/**
*
*/
UCLASS()
class FIGHTCOMPONENT_API UCreatureStateContainer : public UObject
{
	GENERATED_BODY()
protected:
	TArray<TScriptInterface<IStateSourceInterface> > container;
public:

	bool IsActive();

	void Add(const TScriptInterface<IStateSourceInterface>& source);

	void Remove(const TScriptInterface<IStateSourceInterface>& source);

	void Clear();
};