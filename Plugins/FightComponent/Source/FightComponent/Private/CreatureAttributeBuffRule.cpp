// Fill out your copyright notice in the Description page of Project Settings.

#include "FightComponentPrivatePCH.h"
#include "CreatureAttributeBuffRule.h"


void UCreatureAttributeBuffRule::InitRule()
{
	BuffLevelCount = FMath::Max(BuffLevelEnum->NumEnums(),1);
}

void UCreatureAttributeBuffRule::OnCompute_Implementation(ACreature* Creature, UPARAM(Ref)TArray<FAttribute>& AttributeContainer)
{
}

uint8 UCreatureAttributeBuffRule::GetPercentBuffTraget_Implementation(uint8 BuffLevel)
{
	return BuffLevelCount-1;
}

void UCreatureAttributeBuffRule::ClampBuff_Implementation(ACreature* Creature, uint8 BuffLevel, UPARAM(Ref) FAttribute & Attribute)
{
}
