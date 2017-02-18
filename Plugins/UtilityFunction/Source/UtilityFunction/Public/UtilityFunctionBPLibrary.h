// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Engine.h"
#include "UtilityFunctionBPLibrary.generated.h"

/* 
*	Function library class.
*	Each function in it is expected to be static and represents blueprint node that can be called in any blueprint.
*
*	When declaring function you can define metadata for the node. Key function specifiers will be BlueprintPure and BlueprintCallable.
*	BlueprintPure - means the function does not affect the owning object in any way and thus creates a node without Exec pins.
*	BlueprintCallable - makes a function which can be executed in Blueprints - Thus it has Exec pins.
*	DisplayName - full name of the node, shown when you mouse over the node and in the blueprint drop down menu.
*				Its lets you name the node using characters not allowed in C++ function names.
*	CompactNodeTitle - the word(s) that appear on the node.
*	Keywords -	the list of keywords that helps you to find node when you search for it using Blueprint drop-down menu. 
*				Good example is "Print String" node which you can find also by using keyword "log".
*	Category -	the category your node will be under in the Blueprint drop-down menu.
*
*	For more info on custom blueprint nodes visit documentation:
*	https://wiki.unrealengine.com/Custom_Blueprint_Node_Creation
*/
UCLASS()
class UUtilityFunctionBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Utility|World")
	static UWorld* GetWorldFromActor(AActor* actor);


	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Utility|World")
	static UWorld* GetWorldFromComponent(UActorComponent* component);

	UFUNCTION(BlueprintCallable, Category = "Utility|Class")
	static void GetAllSubClass(UClass* BaseClass, TArray<UClass*>& Result);


	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Utility|Class")
	static UClass* GetParentClass(UClass* _Class);

	UFUNCTION(BlueprintCallable, Category = "Utility|DataTable", CustomThunk, meta = (CustomStructureParam = "Data"))
	static bool GetCustomDataFromTable(UDataTable* Table,FName RowName, UProperty* & Data);

	DECLARE_FUNCTION(execGetCustomDataFromTable)
	{
		P_GET_OBJECT(UDataTable, Table);
		P_GET_PROPERTY(UNameProperty, RowName);

		// Steps into the stack, walking to the next property in it
		Stack.Step(Stack.Object, NULL);
		UStructProperty* StructProperty = ExactCast<UStructProperty>(Stack.MostRecentProperty);
		void* StructPtr = Stack.MostRecentPropertyAddress;
		P_FINISH;

		bool bFoundRow = false;

		if (Table)
		{
			UScriptStruct* StructType = Table->RowStruct;

			if (Table->RowStruct == StructProperty->Struct)
			{
				void* RowPtr = Table->FindRowUnchecked(RowName);
				if (RowPtr != NULL)
				{
					StructType->CopyScriptStruct(StructPtr, RowPtr);
					bFoundRow = true;
				}
			}
		}
		P_NATIVE_BEGIN;
		*(bool*) RESULT_PARAM = bFoundRow;
		P_NATIVE_END;
	}
};
