// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "FightConfigerInterface.h"
#include "CreatureAttributeFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class UCreatureAttributeFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()
	
public:

	TSharedPtr<FRegexPattern> NameRegexPattern;
	UCreatureAttributeRule* AttributeRule;

	void ParseAttributeStruct(UScriptStruct* Struct, void* StructPtr, TArray<FAttributeBuff>& AttributeArray);

	UFUNCTION(BlueprintCallable, Category = "Creature|Attribute")
	static bool GetFightConfiger(TScriptInterface<IFightConfigerInterface>& FightConfiger);

	UFUNCTION(BlueprintCallable, Category = "Creature|Attribute")
	static void ConvertBuffToPercent( UPARAM(Ref) TArray<FAttributeBuff>& AttributeList);

	UFUNCTION(BlueprintCallable, Category = "CreatureAttribute", CustomThunk, meta = (CustomStructureParam = "Attribute"))
	static TArray<FAttributeBuff> ConvertStructToAttribute(UProperty* Attribute);
	DECLARE_FUNCTION(execConvertStructToAttribute)
	{
		//P_GET_ARRAY_REF(TArray<FAttributeBuff>,AttributeList);
		Stack.Step(Stack.Object, NULL);
		UStructProperty* StructProperty = ExactCast<UStructProperty>(Stack.MostRecentProperty);
		void* StructPtr = Stack.MostRecentPropertyAddress;
		P_FINISH;
		UScriptStruct* Struct = StructProperty->Struct;
		TArray<FAttributeBuff> AttributeList;
		ParseAttributeStruct(Struct, StructPtr, AttributeList);
		P_NATIVE_BEGIN;
		*(TArray<FAttributeBuff>*) RESULT_PARAM = AttributeList;
		P_NATIVE_END;
	}
};
