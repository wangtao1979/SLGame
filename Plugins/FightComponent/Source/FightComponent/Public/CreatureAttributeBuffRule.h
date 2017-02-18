#pragma once

#include "Object.h"
#include "FightDef.h"
#include "CreatureAttributeBuffRule.generated.h"

/**
*
*/
UCLASS(BlueprintType, Blueprintable)
class FIGHTCOMPONENT_API UCreatureAttributeBuffRule : public UObject
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Creature|Attribute")
	UEnum* BuffLevelEnum;

	UPROPERTY(BlueprintReadOnly, Category = "Creature|Attribute")
	int32 BuffLevelCount;
public:

	UFUNCTION(BlueprintCallable, Category = "Creature|Attribute")
	void InitRule();

	UFUNCTION(BlueprintImplementableEvent, Category = "Creature|Attribute")
	void OnInitRule();


	UFUNCTION(BlueprintNativeEvent, Category = "Creature|Attribute")
	void OnCompute(ACreature* Creature,UPARAM(Ref) TArray<FAttribute> & AttributeContainer);
	void OnCompute_Implementation(ACreature* Creature, UPARAM(Ref) TArray<FAttribute> & AttributeContainer);


	UFUNCTION(BlueprintNativeEvent, Category = "Creature|Attribute")
	uint8 GetPercentBuffTraget(uint8 BuffLevel);
	uint8 GetPercentBuffTraget_Implementation(uint8 BuffLevel);


	UFUNCTION(BlueprintNativeEvent, Category = "Creature|Attribute")
	void ClampBuff(ACreature* Creature, uint8 BuffLevel, UPARAM(Ref) FAttribute & Attribute);
	void ClampBuff_Implementation(ACreature* Creature, uint8 BuffLevel, UPARAM(Ref) FAttribute & Attribute);

	UFUNCTION(BlueprintCallable, Category = "Creature|Attribute")
	FORCEINLINE int32 GetBuffLevelCount()
	{
		return BuffLevelCount;
	}
};