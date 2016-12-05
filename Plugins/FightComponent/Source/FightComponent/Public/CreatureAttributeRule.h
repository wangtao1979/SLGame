#pragma once

#include "Object.h"
#include "CreatureAttributeRule.generated.h"



//DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Modify, uint8, Index, float, Value);

/**
*
*/
UCLASS(BlueprintType, Blueprintable)
class UCreatureAttributeRule : public UObject
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintReadOnly, Category = CreatureAttribute)
	int AttributeSize;

	UPROPERTY(BlueprintReadOnly, Category = CreatureAttribute)
	TArray<FString> AttributeNameList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CreatureAttribute)
	UEnum* AttributeEnum;
public:

	UFUNCTION(BlueprintImplementableEvent, Category = "CreatureAttribute")
	void InitRule();

	UFUNCTION(BlueprintCallable, Category = "CreatureAttribute", CustomThunk, meta = (CustomStructureParam = "Attribute"))
	void BindAttriibuteDefine(UProperty* Attribute);

	DECLARE_FUNCTION(execBindAttriibuteDefine)
	{
		Stack.Step(Stack.Object, NULL);
		UStructProperty* StructProperty = ExactCast<UStructProperty>(Stack.MostRecentProperty);
		void* StructPtr = Stack.MostRecentPropertyAddress;
		P_FINISH;

		UScriptStruct* Struct = StructProperty->Struct;

		AttributeSize = Struct->PropertiesSize;
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
			AttributeNameList.Add(VariableName);
		}
	}
};