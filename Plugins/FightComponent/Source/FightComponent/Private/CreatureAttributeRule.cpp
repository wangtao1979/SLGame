// Fill out your copyright notice in the Description page of Project Settings.

#include "FightComponentPrivatePCH.h"
#include "CreatureAttributeRule.h"

/**UCreatureAttributeRule::UCreatureAttributeRule():NameRegexPattern(TEXT("(\\w+)"))
{

}*/
void UCreatureAttributeRule::InitRule()
{
	OnInit();
}


int UCreatureAttributeRule::GetAttrubuteNumber() const
{
	return AttributeEnum->NumEnums();
}



void UCreatureAttributeRule::ParseAttributeStruct(UScriptStruct* Struct, void* StructPtr, TArray<float> AttributeArray)
{
	check(Struct->IsValidLowLevel() && StructPtr != nullptr);
	AttributeArray.SetNumZeroed(AttributeEnum->NumEnums());
	for (TFieldIterator<UProperty> It(Struct); It; ++It)
	{
		UProperty* Property = *It;
		FString VariableName = Property->GetName();
		const FRegexPattern NameRegexPattern(TEXT("(\\w+)"));
		FRegexMatcher matcher(NameRegexPattern, VariableName);
		if (matcher.FindNext())
		{
			VariableName = matcher.GetCaptureGroup(0);
			int32 index = AttributeEnum->FindEnumIndex(FName(*VariableName));
			if (index != INDEX_NONE)
			{
				void* ValuePtr = Property->ContainerPtrToValuePtr<void>(StructPtr, 0);
				UNumericProperty *NumericProperty = Cast<UNumericProperty>(Property);
				if (NumericProperty && NumericProperty->IsFloatingPoint())
				{
					AttributeArray[index] = NumericProperty->GetFloatingPointPropertyValue(ValuePtr);
				}
			}
		}
	}
}