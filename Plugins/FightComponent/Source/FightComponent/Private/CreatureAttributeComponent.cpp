// Fill out your copyright notice in the Description page of Project Settings.

#include "FightComponentPrivatePCH.h"
#include "CreatureAttributeComponent.h"

// Sets default values for this component's properties
UCreatureAttributeComponent::UCreatureAttributeComponent():
	AttributeRule(nullptr),
	AttributeBuffRule(nullptr)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UCreatureAttributeComponent::BeginPlay()
{
	Super::BeginPlay();

	TScriptInterface<IFightConfigerInterface> FightConfiger;
	if (UCreatureAttributeFunctionLibrary::GetFightConfiger(FightConfiger))
	{
		AttributeRule = IFightConfigerInterface::Execute_GetAttributeRule(FightConfiger.GetObject());
		AttributeBuffRule = IFightConfigerInterface::Execute_GetAttributeBuffRule(FightConfiger.GetObject());
	}
	if (AttributeRule == nullptr)
	{
		AttributeRule = NewObject<UCreatureAttributeRule>(this);
	}
	if (AttributeBuffRule==nullptr)
	{
		AttributeBuffRule = NewObject<UCreatureAttributeBuffRule>(this);
	}
	// init attribute size 
	AttributeCount = AttributeRule->GetAttribute()->NumEnums();
	AttributeList.AddZeroed(AttributeCount);
	DynamicAttributeList.AddZeroed(AttributeCount);

	// init attribute buff size 
	uint32 BuffLevelNumber = AttributeBuffRule->GetBuffLevelCount();
	BaseAttributeIndex = BuffLevelNumber-1;
	BuffSourceContainer.AddDefaulted(BuffLevelNumber);
	BuffAttributeList.AddDefaulted(BuffLevelNumber);
	for (int32 i = 0; i < BuffAttributeList.Num(); i++)
	{
		BuffAttributeList[i].Init(AttributeCount);
	}

	AActor* Owner = GetOwner();
	if (Owner->GetClass()->IsChildOf(ACreature::StaticClass()))
	{
		OwnerCreature = Cast<ACreature>(Owner);
	}

	// add base attribute
	ComputeBaseAttribute();
	ResetAllDynamicAttribute();
}


// Called every frame
void UCreatureAttributeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


float UCreatureAttributeComponent::GetAttribute(uint8 type)
{
	if (type >= AttributeList.Num())
	{
		return 0.0f;
	}
	check(type < AttributeList.Num());
	return AttributeList[type];
}

void UCreatureAttributeComponent::AddBuff(const TScriptInterface<IAttributeSourceInterface>& source)
{
	uint8 index = source->Execute_GetBuffLevel(source.GetObject());
	check(index < BuffSourceContainer.Num());
	BuffSourceContainer[index].AddBuff(source);
}

void UCreatureAttributeComponent::RemoveBuff(const TScriptInterface<IAttributeSourceInterface>& source)
{
	uint8 index = source->Execute_GetBuffLevel(source.GetObject());
	check(index < BuffSourceContainer.Num());
	BuffSourceContainer[index].RemoveBuff(source);
}

float UCreatureAttributeComponent::GetDynamicAttribute(uint8 type)
{
	return DynamicAttributeList[type];
}

float UCreatureAttributeComponent::GetBaseAttribute(uint8 type)
{
	return BuffAttributeList[BaseAttributeIndex].Final[type];
}

void UCreatureAttributeComponent::SetDynamicAttribute(uint8 type, float v)
{
	DynamicAttributeList[type] = v;
	FMath::Clamp(DynamicAttributeList[type], 0.0f, GetAttribute(type));
}


void UCreatureAttributeComponent::AddDynamicAttribute(uint8 type, float v)
{
	DynamicAttributeList[type] += v;
	FMath::Clamp(DynamicAttributeList[type], 0.0f, GetAttribute(type));
}

void UCreatureAttributeComponent::ResetDynamicAttribute(uint8 type)
{
	DynamicAttributeList[type] = AttributeList[type];
}

void UCreatureAttributeComponent::ResetAllDynamicAttribute()
{
	for (int32 i = 0; i < AttributeCount; i++)
	{
		ResetDynamicAttribute(i);
	}
}


float UCreatureAttributeComponent::GetBuffAttribute(uint8 BuffLevel, uint8 type)
{
	check(BuffLevel < BuffAttributeList.Num());
	check(type < BuffAttributeList[BuffLevel].Final.Num());
	return BuffAttributeList[BuffLevel].Final[type];
}

void UCreatureAttributeComponent::ComputeBaseAttribute()
{
	AActor* Owner = GetOwner();
	if (Owner->GetClass()->ImplementsInterface(UAttributeSourceInterface::StaticClass()))
	{
		FBuffSourceContainer & BaseBuff = BuffSourceContainer[BaseAttributeIndex];
		FAttribute& Attribute = BuffAttributeList[BaseAttributeIndex];
		BaseBuff.Clear();
		Attribute.Clear();
		BaseBuff.AddBuff(OwnerCreature);
		BaseBuff.ComputeBuff(Attribute);
		TArray<float> ZeroArray;
		ZeroArray.AddZeroed(AttributeCount);
		Attribute.Compute(ZeroArray);
	}
	ComputeAttribute();
}

void UCreatureAttributeComponent::ComputeAttribute()
{
	for (int32 i = 0; i < BaseAttributeIndex; i++)
	{
		FBuffSourceContainer & BaseBuff = BuffSourceContainer[i];
		FAttribute& Attribute = BuffAttributeList[i];
		Attribute.Clear();
		BaseBuff.ComputeBuff(Attribute);
		AttributeBuffRule->ClampBuff(OwnerCreature, i, Attribute);
		uint8 BuffLevel = AttributeBuffRule->GetPercentBuffTraget(i);
		Attribute.Compute(BuffAttributeList[BuffLevel].Final);
	}
	AttributeBuffRule->OnCompute(OwnerCreature, BuffAttributeList);
	for (float& value : AttributeList)
	{
		value = 0.0f;
	}
	for (int32 i = 0; i <= BaseAttributeIndex; i++)
	{
		BuffAttributeList[i].Count(AttributeList);
	}
	for (int32 i = 0; i < AttributeCount; i++)
	{
		DynamicAttributeList[i] = FMath::Min(DynamicAttributeList[i], AttributeList[i]);
	}
}
