#pragma once

#include "Object.h"
#include "Runtime/Core/Public/Internationalization/Regex.h"
#include "Runtime/Engine/Classes/Engine/DataTable.h"
#include "Runtime/Engine/Classes/Engine/UserDefinedEnum.h"
#include "CreatureAttributeRule.generated.h"



//DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Modify, uint8, Index, float, Value);

/**
*
*/
UCLASS(BlueprintType, Blueprintable)
class FIGHTCOMPONENT_API UCreatureAttributeRule : public UObject
{
	GENERATED_BODY()

	TSharedPtr<FRegexPattern> NameRegexPattern;
	//
	TMap<FString, int32> AttributeNameMap;
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Creature|Attribute")
	UUserDefinedEnum* AttributeEnum;

public:
	UCreatureAttributeRule(const FObjectInitializer& ObjectInitializer);

	void ParseAttributeStruct(UScriptStruct* Struct, void* StructPtr, TArray<float>& AttributeArray);

	//UCreatureAttributeRule();
	void InitRule(class UCreatureAttributeComponent* AttributeComponent);

	UFUNCTION(BlueprintImplementableEvent, Category = "Creature|Attribute")
	void OnInit(class UCreatureAttributeComponent* AttributeComponent);

	UFUNCTION(BlueprintCallable, Category = "Creature|Attribute")
	FORCEINLINE UUserDefinedEnum* GetAttribute() const
	{
		return AttributeEnum;
	}
};