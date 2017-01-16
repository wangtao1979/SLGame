// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtraAINodePrivatePCH.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BTDecorator_BBValueCooldown.h"



UBTDecorator_BBValueCooldown::UBTDecorator_BBValueCooldown(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Blackbroad Value Cooldown";

	// aborting child nodes doesn't makes sense, cooldown starts after leaving this branch
	bAllowAbortChildNodes = false;

	bNotifyTick = false;
	bNotifyDeactivation = true;
}

void UBTDecorator_BBValueCooldown::PostLoad()
{
	Super::PostLoad();
	bNotifyTick = (FlowAbortMode != EBTFlowAbortMode::None);
}

bool UBTDecorator_BBValueCooldown::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	FBTBBCooldownDecoratorMemory* DecoratorMemory = reinterpret_cast<FBTBBCooldownDecoratorMemory*>(NodeMemory);
	const float TimePassed = (OwnerComp.GetWorld()->GetTimeSeconds() - DecoratorMemory->LastUseTimestamp);
	float CoolDownTime = GetCooldownTime(OwnerComp);
	return TimePassed >= CoolDownTime;
}

void UBTDecorator_BBValueCooldown::InitializeMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTMemoryInit::Type InitType) const
{
	FBTBBCooldownDecoratorMemory* DecoratorMemory = reinterpret_cast<FBTBBCooldownDecoratorMemory*>(NodeMemory);
	if (InitType == EBTMemoryInit::Initialize)
	{
		DecoratorMemory->LastUseTimestamp = -FLT_MAX;
	}

	DecoratorMemory->bRequestedRestart = false;
}

void UBTDecorator_BBValueCooldown::OnNodeDeactivation(FBehaviorTreeSearchData& SearchData, EBTNodeResult::Type NodeResult)
{
	FBTBBCooldownDecoratorMemory* DecoratorMemory = GetNodeMemory<FBTBBCooldownDecoratorMemory>(SearchData);
	DecoratorMemory->LastUseTimestamp = SearchData.OwnerComp.GetWorld()->GetTimeSeconds();
	DecoratorMemory->bRequestedRestart = false;
}

void UBTDecorator_BBValueCooldown::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	FBTBBCooldownDecoratorMemory* DecoratorMemory = reinterpret_cast<FBTBBCooldownDecoratorMemory*>(NodeMemory);
	if (!DecoratorMemory->bRequestedRestart)
	{
		const float TimePassed = (OwnerComp.GetWorld()->GetTimeSeconds() - DecoratorMemory->LastUseTimestamp);
		float CoolDownTime = GetCooldownTime(OwnerComp);
		if (TimePassed >= CoolDownTime)
		{
			DecoratorMemory->bRequestedRestart = true;
			OwnerComp.RequestExecution(this);
		}
	}
}

void UBTDecorator_BBValueCooldown::DescribeRuntimeValues(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const
{
	Super::DescribeRuntimeValues(OwnerComp, NodeMemory, Verbosity, Values);

	FBTBBCooldownDecoratorMemory* DecoratorMemory = reinterpret_cast<FBTBBCooldownDecoratorMemory*>(NodeMemory);
	const float TimePassed = OwnerComp.GetWorld()->GetTimeSeconds() - DecoratorMemory->LastUseTimestamp;
	float CoolDownTime = GetCooldownTime(OwnerComp);
	if (TimePassed < CoolDownTime)
	{
		Values.Add(FString::Printf(TEXT("%s in %ss"),
			(FlowAbortMode == EBTFlowAbortMode::None) ? TEXT("unlock") : TEXT("restart"),
			*FString::SanitizeFloat(CoolDownTime - TimePassed)));
	}
}

uint16 UBTDecorator_BBValueCooldown::GetInstanceMemorySize() const
{
	return sizeof(FBTBBCooldownDecoratorMemory);
}



float UBTDecorator_BBValueCooldown::GetCooldownTime(const UBehaviorTreeComponent& OwnerComp) const
{
	const UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (BlackboardComp == NULL)
	{
		return 0.0f;
	}
	return BlackboardComp->GetValueAsFloat(CoolDownTimeKey.SelectedKeyName);
}