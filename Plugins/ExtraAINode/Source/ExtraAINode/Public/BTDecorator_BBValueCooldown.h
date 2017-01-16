// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Runtime/AIModule/Classes/BehaviorTree/BTDecorator.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BehaviorTreeTypes.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BTDecorator_BBValueCooldown.generated.h"

struct FBTBBCooldownDecoratorMemory
{
	float LastUseTimestamp;
	uint8 bRequestedRestart : 1;
};

UCLASS(Blueprintable, BlueprintType)
class UBTDecorator_BBValueCooldown : public UBTDecorator
{
public:

	GENERATED_UCLASS_BODY()

	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector CoolDownTimeKey;

	//~ Begin UObject Interface
	virtual void PostLoad() override;
	//~ End UObject Interface

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	virtual void InitializeMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTMemoryInit::Type InitType) const override;
	virtual uint16 GetInstanceMemorySize() const override;
	virtual void DescribeRuntimeValues(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const override;

	float GetCooldownTime(const UBehaviorTreeComponent& OwnerComp) const;
protected:

	virtual void OnNodeDeactivation(FBehaviorTreeSearchData& SearchData, EBTNodeResult::Type NodeResult) override;
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};
