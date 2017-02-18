// Fill out your copyright notice in the Description page of Project Settings.

#include "FightComponentPrivatePCH.h"
#include "CreatureStateComponent.h"




// Sets default values for this component's properties
UCreatureStateComponent::UCreatureStateComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UCreatureStateComponent::BeginPlay()
{
	Super::BeginPlay();
	Container.SetNumUninitialized(StateEnum->NumEnums());
	StateNumber = StateEnum->NumEnums();
	for (int32 index=0; index<StateNumber; index++)
	{
		Container[index] = NewObject<UCreatureStateContainer>();
	}
}


// Called every frame
void UCreatureStateComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}


void UCreatureStateComponent::AddState(const TScriptInterface<IStateSourceInterface>& source)
{
	TArray<uint8> StateList;
	IStateSourceInterface::Execute_GetState(source.GetObject(), StateList);
	for (uint8 index : StateList)
	{
		if (index >= 0 && index<StateNumber)
		{
			Container[index]->Add(source);
		}
	}
}

void UCreatureStateComponent::RemoveState(const TScriptInterface<IStateSourceInterface>& source)
{
	TArray<uint8> StateList;
	IStateSourceInterface::Execute_GetState(source.GetObject(), StateList);
	for (uint8 index : StateList)
	{
		if (index >= 0 && index < StateNumber)
		{
			Container[index]->Remove(source);
		}
	}
}

bool UCreatureStateComponent::IsStateActive(uint8 state)
{
	if (state >= 0 && state < StateNumber)
	{
		return Container[state]->IsActive();
	}
	return false;
}

void UCreatureStateComponent::InitializeState()
{

	for (UCreatureStateContainer* sc: Container)
	{
		if (sc->IsValidLowLevelFast()) 
		{
			sc->Clear();
		}
	}
}