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
class UCreatureAttributeComponent : public UActorComponent
{
	GENERATED_BODY()
private:
	TMap<FString, uint8> Name2IndexMapping;
	
	int MaxAttributeEntry;

	TArray<FAttributeBuffContainer> BuffContainerList;

	UCreatureAttributeRule* AttruteRule;

	UCreatureAttributeBuffRule* AttruteBuffRule;
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Classes)
	TSubclassOf<class UCreatureAttributeRule> DefaultAttributeRule;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Classes)
	TSubclassOf<class UCreatureAttributeBuffRule> DefaultAttributeBuffRule;

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
	float GetAttribute(uint8 type);

	UFUNCTION(BlueprintCallable, Category = "CreatureAttribute")
	void AddBuff(const TScriptInterface<IAttributeSourceInterface>& source);

	UFUNCTION(BlueprintCallable, Category = "CreatureAttribute")
	void RemoveBuff(const TScriptInterface<IAttributeSourceInterface>& source);
};
