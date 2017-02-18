// Fill out your copyright notice in the Description page of Project Settings.

#include "FightComponentPrivatePCH.h"
#include "CreatureAttributeRule.h"

UCreatureAttributeRule::UCreatureAttributeRule(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{

}
void UCreatureAttributeRule::InitRule()
{
	check(AttributeEnum);
	for (int32 i=0;i<AttributeEnum->NumEnums();i++)
	{
		AttributeNameMap.Add(AttributeEnum->GetEnumText(i).ToString(), i);
	}
}

uint8 UCreatureAttributeRule::FindIndex(FString& name)
{
	return AttributeNameMap.FindRef(name);
}
