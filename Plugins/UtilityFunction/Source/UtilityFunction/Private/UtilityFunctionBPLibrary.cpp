// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "UtilityFunctionPrivatePCH.h"
#include "UtilityFunctionBPLibrary.h"

UUtilityFunctionBPLibrary::UUtilityFunctionBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

UWorld* UUtilityFunctionBPLibrary::GetWorldFromActor(AActor* actor)
{
	if (actor!= nullptr && actor->IsValidLowLevelFast())
	{
		return actor->GetWorld();
	}
	else
	{
		return nullptr;
	}
}


UWorld* UUtilityFunctionBPLibrary::GetWorldFromComponent(UActorComponent* component)
{
	if (component != nullptr && component->IsValidLowLevelFast())
	{
		return component->GetWorld();
	}
	else
	{
		return nullptr;
	}
}


void UUtilityFunctionBPLibrary::GetAllSubClass(UClass* BaseClass, TArray<UClass*>& Result)
{
	for (TObjectIterator<UClass> It; It; ++It)
	{
		if (It->IsChildOf(BaseClass) && BaseClass!=*It)
		{
			Result.Add(*It);
		}
	}
}

UClass* UUtilityFunctionBPLibrary::GetParentClass(UClass* _Class)
{
	check(_Class!=nullptr);
	return _Class->GetSuperClass();
}