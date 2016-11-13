// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "FightDef.h"
#include "AttributeSourceinterface.h"
#include "CreatureAttributeComponent.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class UCreatureAttributeComponent : public UActorComponent
{
	GENERATED_BODY()
private:
	TMap<FString, uint8> Name2IndexMapping;
	
	int MaxAttributeEntry;

public:
	inline int GetAttribyteEnty()
	{
		return MaxAttributeEntry;
	}
public:
	// Sets default values for this component's properties
	UCreatureAttributeComponent();

	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "CreatureAttribute")
	float GetByIndex(uint8 type);

	UFUNCTION(BlueprintCallable, Category = "CreatureAttribute")
	float GetByName(FString type);

	UFUNCTION(BlueprintCallable, Category = "CreatureAttribute")
	void AddBuff(const TScriptInterface<IAttributeSourceInterface>& source);

	UFUNCTION(BlueprintCallable, Category = "CreatureAttribute")
	void RemoveBuff(const TScriptInterface<IAttributeSourceInterface>& source);

	UFUNCTION(BlueprintCallable, Category = "CreatureAttribute", CustomThunk, meta = (CustomStructureParam = "Attribute"))
	void SetBaseStruct(UProperty* Attribute);

	DECLARE_FUNCTION(execSetBaseStruct)
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
			Name2IndexMapping.Add(VariableName, index++);

			//UE_LOG(FightLog, Log, TEXT("struct name %s : index = %d"), *VariableName, *Name2IndexMapping.Find(VariableName));

			// Never assume ArrayDim is always 1
			for (int32 ArrayIndex = 0; ArrayIndex < Property->ArrayDim; ArrayIndex++)
			{
				// This grabs the pointer to where the property value is stored
				void* ValuePtr = Property->ContainerPtrToValuePtr<void>(StructPtr, ArrayIndex);
				float value = 0;
				UNumericProperty *NumericProperty = Cast<UNumericProperty>(Property);
				if (NumericProperty && NumericProperty->IsFloatingPoint())
				{
					value = NumericProperty->GetFloatingPointPropertyValue(ValuePtr);
					//UE_LOG(FightLog, Log, TEXT("struct name %s : %f"), *VariableName, value);
					//UE_LOG(FightLog, Warning, TEXT("struct name :%s value=\n"),VariableName);
				}
			}
		}
	}
};
