// Fill out your copyright notice in the Description page of Project Settings.

#include "FightComponentPrivatePCH.h"
#include "CreatureAttributeRule.h"

UCreatureAttributeRule::UCreatureAttributeRule(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer),
	NameRegexPattern(new FRegexPattern(TEXT("(^_)_(\\w+)_(\\w+)")))
{

}
void UCreatureAttributeRule::InitRule(class UCreatureAttributeComponent* AttributeComponent)
{
	check(AttributeEnum);
	for (int32 i=0;i< AttributeEnum->NumEnums();i++)
	{
		AttributeNameMap.Add(AttributeEnum->GetEnumText(i).ToString(), i);
	}
	OnInit(AttributeComponent);
}


void UCreatureAttributeRule::ParseAttributeStruct(UScriptStruct* Struct, void* StructPtr, TArray<float>& AttributeArray)
{
	check(Struct->IsValidLowLevel() && StructPtr != nullptr);
	AttributeArray.SetNumZeroed(AttributeEnum->NumEnums());
	for (TFieldIterator<UProperty> It(Struct); It; ++It)
	{
		UProperty* Property = *It;
		FString VariableName = Property->GetName();
		FRegexMatcher matcher(*NameRegexPattern, VariableName);
		if (matcher.FindNext())
		{
			VariableName = matcher.GetCaptureGroup(1);
			int32 index = *AttributeNameMap.Find(VariableName);
			void* ValuePtr = Property->ContainerPtrToValuePtr<void>(StructPtr, 0);
			UNumericProperty *NumericProperty = Cast<UNumericProperty>(Property);
			if (NumericProperty && NumericProperty->IsFloatingPoint())
			{
				AttributeArray[index] = NumericProperty->GetFloatingPointPropertyValue(ValuePtr);
			}
		}
	}
}