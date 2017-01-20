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
	void ParseAttributeStruct(UScriptStruct* Struct, void* StructPtr, UUserDefinedEnum* AttributeEnum, TArray<float>& AttributeArray);


	UFUNCTION(BlueprintCallable, Category = "Creature|Attribute")
	bool GetAttributeFromTable(UDataTable* AttributeTable, FName Key, UUserDefinedEnum* AttributeEnum, TArray<float>& AttributeArray);

	UFUNCTION(BlueprintCallable, Category = "CreatureAttribute", CustomThunk, meta = (CustomStructureParam = "Attribute"))
	static TArray<float> ConvertStructToAttribute(UUserDefinedEnum* AttributeEnum,UProperty* Attribute);

	DECLARE_FUNCTION(execConvertStructToAttribute)
	{

		P_GET_OBJECT(UUserDefinedEnum, AttributeEnum);

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
		TArray<float> AttributeList;
		
		ParseAttributeStruct(Struct, StructPtr, AttributeEnum, AttributeList);

		*(TArray<float>*) RESULT_PARAM = AttributeList;
	}
};
