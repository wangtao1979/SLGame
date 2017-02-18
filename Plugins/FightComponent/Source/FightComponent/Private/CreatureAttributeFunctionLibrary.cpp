// Fill out your copyright notice in the Description page of Project Settings.

#include "FightComponentPrivatePCH.h"
#include "FightDef.h"
#include "CreatureAttributeFunctionLibrary.h"

UCreatureAttributeFunctionLibrary::UCreatureAttributeFunctionLibrary(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer),
	NameRegexPattern(new FRegexPattern(TEXT("(\\w+)_(\\w+)_(\\w+)"))),
	AttributeRule(nullptr)
{

}

void UCreatureAttributeFunctionLibrary::ConvertBuffToPercent(TArray<FAttributeBuff>& AttributeList)
{
	for (int i = 0; i < AttributeList.Num(); i++)
	{
		AttributeList[i].IsPercent = true;
	}
}

void UCreatureAttributeFunctionLibrary::ParseAttributeStruct(UScriptStruct* Struct, void* StructPtr, TArray<FAttributeBuff>& AttributeArray)
{
	if (AttributeRule == nullptr)
	{
		TScriptInterface<IFightConfigerInterface> FightConfiger;
		if (UCreatureAttributeFunctionLibrary::GetFightConfiger(FightConfiger))
		{
			AttributeRule = IFightConfigerInterface::Execute_GetAttributeRule(FightConfiger.GetObject());
		}
	}

	check(Struct->IsValidLowLevel() && StructPtr != nullptr);
	for (TFieldIterator<UProperty> It(Struct); It; ++It)
	{
		UProperty* Property = *It;
		FString VariableName = Property->GetName();
		FRegexMatcher matcher(*NameRegexPattern, VariableName);
		if (matcher.FindNext())
		{
			VariableName = matcher.GetCaptureGroup(1);
			uint8 Type = AttributeRule->FindIndex(VariableName);
			void* ValuePtr = Property->ContainerPtrToValuePtr<void>(StructPtr, 0);
			UNumericProperty *NumericProperty = Cast<UNumericProperty>(Property);
			if (NumericProperty && NumericProperty->IsFloatingPoint())
			{
				float Value = NumericProperty->GetFloatingPointPropertyValue(ValuePtr);
				if (Value != 0.0f)
				{
					AttributeArray.Add(FAttributeBuff(Type,Value,false));
				}
			}
		}
	}
}


bool UCreatureAttributeFunctionLibrary::GetFightConfiger(TScriptInterface<IFightConfigerInterface>& FightConfiger)
{
	if (GEngine->GameSingleton && GEngine->GameSingleton->GetClass()->ImplementsInterface(UFightConfigerInterface::StaticClass()))
	{
		FightConfiger.SetObject(GEngine->GameSingleton);
		void* IAddress = GEngine->GameSingleton->GetInterfaceAddress(UFightConfigerInterface::StaticClass());
		FightConfiger.SetInterface(IAddress);
		return true;
	}
	else
	{
		FightConfiger.SetObject(nullptr);
		return false;
	}
}
