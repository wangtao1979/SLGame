// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "CreatureAttributeFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class UCreatureAttributeFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "CreatureAttribute", CustomThunk, meta = (CustomStructureParam = "Attribute"))
	static TArray<float> AttributeStructToValueArray(UProperty* Attribute);

	DECLARE_FUNCTION(execAttributeStructToValueArray)
	{
		// Steps into the stack, walking to the next property in it
		Stack.Step(Stack.Object, NULL);

		// Grab the last property found when we walked the stack
		// This does not contains the property value, only its type information
		UStructProperty* StructProperty = ExactCast<UStructProperty>(Stack.MostRecentProperty);

		// Grab the base address where the struct actually stores its data
		// This is where the property value is truly stored
		void* StructPtr = Stack.MostRecentPropertyAddress;
		// We need this to wrap up the stack
		P_FINISH;
		// Walk the structs' properties
		UScriptStruct* Struct = StructProperty->Struct;
		uint8 index = 0;
		TArray<float> AttributeList;
		for (TFieldIterator<UProperty> It(Struct); It; ++It)
		{
			UProperty* Property = *It;

			// This grabs the pointer to where the property value is stored
			void* ValuePtr = Property->ContainerPtrToValuePtr<void>(StructPtr, 0);
			UNumericProperty *NumericProperty = Cast<UNumericProperty>(Property);
			if (NumericProperty && NumericProperty->IsFloatingPoint())
			{
				AttributeList.Add(NumericProperty->GetFloatingPointPropertyValue(ValuePtr));
			}
		}
		*(TArray<float>*) RESULT_PARAM = AttributeList;
	}


	UFUNCTION(BlueprintCallable, Category = "CreatureAttribute", CustomThunk, meta = (CustomStructureParam = "Attribute"))
	static TArray<FString> AttributeStructToNameArray(UProperty* Attribute);

	DECLARE_FUNCTION(execAttributeStructToNameArray)
	{
		// Steps into the stack, walking to the next property in it
		Stack.Step(Stack.Object, NULL);

		// Grab the last property found when we walked the stack
		// This does not contains the property value, only its type information
		UStructProperty* StructProperty = ExactCast<UStructProperty>(Stack.MostRecentProperty);

		// Grab the base address where the struct actually stores its data
		// This is where the property value is truly stored
		void* StructPtr = Stack.MostRecentPropertyAddress;

		// We need this to wrap up the stack
		P_FINISH;

		// Iterate through the struct

		// Walk the structs' properties
		UScriptStruct* Struct = StructProperty->Struct;
		uint8 index = 0;
		TArray<FString> NameList;
		for (TFieldIterator<UProperty> It(Struct); It; ++It)
		{
			UProperty* Property = *It;

			// This is the variable name if you need it
			FString VariableName = Property->GetName();
			FString left;
			FString right;
			bool succ = VariableName.Split("_", &left, &right, ESearchCase::CaseSensitive, ESearchDir::FromStart);
			if (succ)
			{
				VariableName = left;
			}
			NameList.Add(VariableName);
		}
		*(TArray<FString>*) RESULT_PARAM = NameList;
	}
};
