#pragma once

#include "Object.h"
#include "Runtime/Core/Public/Internationalization/Regex.h"
#include "Runtime/Engine/Classes/Engine/DataTable.h"
#include "Runtime/Engine/Classes/Engine/UserDefinedEnum.h"
#include "CreatureAttributeRule.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAttributeModify, uint8, Index, float, Value);

/**
*
*/
UCLASS(BlueprintType, Blueprintable)
class FIGHTCOMPONENT_API UCreatureAttributeRule : public UObject
{
	GENERATED_BODY()
	//
	TMap<FString, uint8> AttributeNameMap;
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Creature|Attribute")
	UUserDefinedEnum* AttributeEnum;

public:
	UCreatureAttributeRule(const FObjectInitializer& ObjectInitializer);

	void InitRule();

	UFUNCTION(BlueprintImplementableEvent, Category = "Creature|Attribute")
	void OnInit();


	UFUNCTION(BlueprintCallable, Category = "Creature|Attribute")
	uint8 FindIndex(UPARAM(Ref) FString& name);

	UFUNCTION(BlueprintCallable, Category = "Creature|Attribute")
	FORCEINLINE UUserDefinedEnum* GetAttribute() const
	{
		return AttributeEnum;
	}
};