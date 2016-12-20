// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "CreatureStateContainer.h"
#include "CreatureStateComponent.generated.h"


/**
 * ½ÇÉ«×´Ì¬
 */
UCLASS(BlueprintType,Blueprintable)
class FIGHTCOMPONENT_API UCreatureStateComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	TArray<UCreatureStateContainer*> Container;
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Creature|State")
	UEnum* StateEnum;

	UPROPERTY(BlueprintReadOnly, Category = "Creature|State")
	int32 StateNumber;
	
public:
	// Sets default values for this component's properties
	UCreatureStateComponent();

	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Creature|State")
	void AddState(const TScriptInterface<IStateSourceInterface>& source);

	UFUNCTION(BlueprintCallable, Category = "Creature|State")
	void RemoveState(const TScriptInterface<IStateSourceInterface>& source);

	UFUNCTION(BlueprintCallable, Category = "Creature|State")
	bool IsStateActive(uint8 state);

	UFUNCTION(BlueprintCallable, Category = "Creature|State")
	void InitializeState();
};
