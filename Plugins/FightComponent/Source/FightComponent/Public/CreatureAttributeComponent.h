// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "FightDef.h"
#include "AttributeSourceinterface.h"
#include "CreatureAttributeBuffRule.h"
#include "CreatureAttributeRule.h"
#include "CreatureAttributeFunctionLibrary.h"
#include "AttributeSourceInterface.h"
#include "CreatureAttributeComponent.generated.h"

USTRUCT(BlueprintType)
struct FBuffSourceContainer
{
	GENERATED_USTRUCT_BODY()

	TMap<UObject*,TArray<FAttributeBuff>> BuffMap;

	~FBuffSourceContainer()
	{
		BuffMap.Empty();
	}

	void Clear()
	{
		BuffMap.Empty();
	}

	void ComputeBuff(FAttribute &Attribute)
	{
		for (TPair<UObject*, TArray<FAttributeBuff>> Pair : BuffMap)
		{
			if (IAttributeSourceInterface::Execute_IsActive(Pair.Key))
			{
				for (FAttributeBuff Buff : Pair.Value)
				{
					if (Buff.IsPercent)
					{
						Attribute.BuffPer[Buff.Type] += Buff.Value;
					}
					else
					{
						Attribute.BuffValue[Buff.Type] += Buff.Value;
					}
				}
			}
		}
	}

	void AddBuff(const TScriptInterface<IAttributeSourceInterface>& source)
	{
		TArray<FAttributeBuff> Array;
		IAttributeSourceInterface::Execute_GetBuffAttribute(source.GetObject(), Array);
		BuffMap.Add(source.GetObject(), Array);
	}
	void RemoveBuff(const TScriptInterface<IAttributeSourceInterface>& source)
	{
		BuffMap.Remove(source.GetObject());
	}
};

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class FIGHTCOMPONENT_API UCreatureAttributeComponent : public UActorComponent
{
	GENERATED_BODY()
private:
	UPROPERTY()
	TArray<FBuffSourceContainer> BuffSourceContainer;
	UPROPERTY()
	TArray<FAttribute> BuffAttributeList;
	UPROPERTY()
	TArray<float> AttributeList;
	UPROPERTY()
	TArray<float> DynamicAttributeList;

	UPROPERTY()
	uint8 BaseAttributeIndex;
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Creature|Attribute")
	UCreatureAttributeRule* AttributeRule;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Creature|Attribute")
	UCreatureAttributeBuffRule* AttributeBuffRule;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Creature|Attribute")
	ACreature * OwnerCreature;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Creature|Attribute")
	int32 AttributeCount;
public:

public:
	// Sets default values for this component's properties
	UCreatureAttributeComponent();

	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Creature|Attribute")
	float GetAttribute(uint8 type);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Creature|Attribute")
	float GetDynamicAttribute(uint8 type);


	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Creature|Attribute")
	float GetBaseAttribute(uint8 type);

	UFUNCTION(BlueprintCallable, Category = "Creature|Attribute")
	void SetDynamicAttribute(uint8 type,float v);

	UFUNCTION(BlueprintCallable, Category = "Creature|Attribute")
	void AddDynamicAttribute(uint8 type, float v);

	UFUNCTION(BlueprintCallable, Category = "Creature|Attribute")
	void ResetDynamicAttribute(uint8 type);


	UFUNCTION(BlueprintCallable, Category = "Creature|Attribute")
	void ResetAllDynamicAttribute();

	UFUNCTION(BlueprintCallable, Category = "Creature|Attribute")
	void AddBuff(const TScriptInterface<IAttributeSourceInterface>& source);

	UFUNCTION(BlueprintCallable, Category = "Creature|Attribute")
	void RemoveBuff(const TScriptInterface<IAttributeSourceInterface>& source);

	UFUNCTION(BlueprintCallable, BlueprintPure,Category = "Creature|Attribute")
	float GetBuffAttribute(uint8 BuffLevel,uint8 type);

	UFUNCTION(BlueprintCallable, Category = "Creature|Attribute")
	void ComputeBaseAttribute();

	UFUNCTION(BlueprintCallable, Category = "Creature|Attribute")
	void ComputeAttribute();
public:
	UFUNCTION(BlueprintCallable, Category = "Creature|Attribute")
	FORCEINLINE uint8 GetBaseAttributeLevel()
	{
		return BaseAttributeIndex;
	}
};
