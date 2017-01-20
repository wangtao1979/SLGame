// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "FightDef.h"
#include "AttributeSourceinterface.h"
#include "CreatureAttributeBuffRule.h"
#include "CreatureAttributeRule.h"
#include "CreatureAttributeComponent.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class FIGHTCOMPONENT_API UCreatureAttributeComponent : public UActorComponent
{
	GENERATED_BODY()
private:

	TArray<FAttributeBuffContainer> BuffContainerList;

	TArray<float> DynamicAttributeList;
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Classes)
	UCreatureAttributeRule* AttributeRule;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Classes)
	UCreatureAttributeBuffRule* AttributeBuffRule;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Classes)
	TSubclassOf<class UCreatureAttributeRule> DefaultAttributeRule;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Classes)
	TSubclassOf<class UCreatureAttributeBuffRule> DefaultAttributeBuffRule;

public:

public:
	// Sets default values for this component's properties
	UCreatureAttributeComponent();

	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "CreatureAttribute")
	float GetAttribute(uint8 type);


	UFUNCTION(BlueprintCallable, Category = "CreatureAttribute")
	float GetDynamicAttribute(uint8 type);


	UFUNCTION(BlueprintCallable, Category = "CreatureAttribute")
	void SetDynamicAttribute(uint8 type,float v);

	UFUNCTION(BlueprintCallable, Category = "CreatureAttribute")
	void AddDynamicAttribute(uint8 type, float v);

	UFUNCTION(BlueprintCallable, Category = "CreatureAttribute")
	void AddBuff(const TScriptInterface<IAttributeSourceInterface>& source);

	UFUNCTION(BlueprintCallable, Category = "CreatureAttribute")
	void RemoveBuff(const TScriptInterface<IAttributeSourceInterface>& source);

	UFUNCTION(BlueprintCallable, Category = "CreatureAttribute", CustomThunk, meta = (CustomStructureParam = "Attribute"))
	void SetBaseAttribute(UProperty* Attribute);

	DECLARE_FUNCTION(execSetBaseAttribute)
	{
		Stack.Step(Stack.Object, NULL);
		UStructProperty* StructProperty = ExactCast<UStructProperty>(Stack.MostRecentProperty);
		void* StructPtr = Stack.MostRecentPropertyAddress;
		P_FINISH;

		UScriptStruct* Struct = StructProperty->Struct;
		TArray<float> AttributeList;
		AttributeRule->ParseAttributeStruct(Struct, StructPtr, AttributeList);
	}
};
