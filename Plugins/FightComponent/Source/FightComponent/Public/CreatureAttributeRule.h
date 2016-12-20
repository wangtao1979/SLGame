#pragma once

#include "Object.h"
#include "Runtime/Core/Public/Internationalization/Regex.h"
#include "Runtime/Engine/Classes/Engine/DataTable.h"
#include "CreatureAttributeRule.generated.h"



//DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Modify, uint8, Index, float, Value);

/**
*
*/
UCLASS(BlueprintType, Blueprintable)
class FIGHTCOMPONENT_API UCreatureAttributeRule : public UObject
{
	GENERATED_BODY()


	//const FRegexPattern NameRegexPattern;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Creature|Attribute")
	UEnum* AttributeEnum;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Creature|Attribute")
	UDataTable* AttributeTable;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Creature|Attribute")
	FName AttributeTableRow;
public:

	//UCreatureAttributeRule();

	void InitRule();

	UFUNCTION(BlueprintImplementableEvent, Category = "Creature|Attribute")
	void OnInit();

	UFUNCTION(BlueprintCallable, Category = "Creature|Attribute")
	int GetAttrubuteNumber() const;

	UFUNCTION(BlueprintCallable, Category = "Creature|Attribute")
	FORCEINLINE UEnum* GetAttibuteEnum() const
	{
		return AttributeEnum;
	}

	void ParseAttributeStruct(UScriptStruct* Struct, void* StructPtr, TArray<float> AttributeArray);

/**	UFUNCTION(BlueprintCallable, Category = "CreatureAttribute", CustomThunk, meta = (CustomStructureParam = "Attribute"))
	void ParseAttributeStruct(UProperty* Attribute, TArray<float> AttributeArray);

	DECLARE_FUNCTION(execParseAttributeStruct)
	{
		P_GET_TARRAY_REF(float, AttributeArray)

		Stack.Step(Stack.Object, NULL);
		UStructProperty* StructProperty = ExactCast<UStructProperty>(Stack.MostRecentProperty);
		void* StructPtr = Stack.MostRecentPropertyAddress;
		P_FINISH;

		AttributeArray.SetNumZeroed(AttributeEnum->NumEnums());

		UScriptStruct* Struct = StructProperty->Struct;
		for (TFieldIterator<UProperty> It(Struct); It; ++It)
		{
			UProperty* Property = *It;
			FString VariableName = Property->GetName();
			const FRegexPattern ElementRegexPattern(TEXT(""));

			FRegexMatcher matcher(ElementRegexPattern, VariableName);
			if (matcher.FindNext())
			{
				VariableName = matcher.GetCaptureGroup(0);
			}
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
	}*/
};