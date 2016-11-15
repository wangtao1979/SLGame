// Fill out your copyright notice in the Description page of Project Settings.

#include "FightComponentPrivatePCH.h"
#include "CreatureAttributeComponent.h"




// Sets default values for this component's properties
UCreatureAttributeComponent::UCreatureAttributeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = false;
	MaxAttributeEntry = 0;

	DefaultAttributeRule = UCreatureAttributeRule::StaticClass();
	DefaultAttributeBuffRule = UCreatureAttributeBuffRule::StaticClass();
}


// Called when the game starts
void UCreatureAttributeComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	AttruteRule = NewObject<UCreatureAttributeRule>(this, DefaultAttributeRule);
	AttruteBuffRule = NewObject<UCreatureAttributeBuffRule>(this, DefaultAttributeBuffRule);
}


// Called every frame
void UCreatureAttributeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


float UCreatureAttributeComponent::GetAttribute(uint8 type)
{
	return 0.0f;
}

void UCreatureAttributeComponent::AddBuff(const TScriptInterface<IAttributeSourceInterface>& source)
{

}

void UCreatureAttributeComponent::RemoveBuff(const TScriptInterface<IAttributeSourceInterface>& source)
{

}