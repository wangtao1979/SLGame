// Fill out your copyright notice in the Description page of Project Settings.

#include "FightComponentPrivatePCH.h"
#include "CreatureStateContainer.h"



void UCreatureStateContainer::Add(const TScriptInterface<IStateSourceInterface>& source)
{
	container.Add(source);
}


void UCreatureStateContainer::Remove(const TScriptInterface<IStateSourceInterface>& source)
{
	container.Remove(source);
}


bool UCreatureStateContainer::IsActive()
{
	for (TScriptInterface<IStateSourceInterface> source : container)
	{
		if (source->IsActive())
		{
			return true;
		}
	}
	return false;
}


void UCreatureStateContainer::Clear()
{
	container.Empty();
}