// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "CreatureStateContainer.h"
#include "CreatureStateComponent.generated.h"


/**
 * ½ÇÉ«×´Ì¬
 */
UCLASS()
class UCreatureStateComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	TArray<UCreatureStateContainer*> Container;
public:
	// Sets default values for this component's properties
	UCreatureStateComponent();

	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Fight")
	void AddState(const TScriptInterface<IStateSourceInterface>& source);

	UFUNCTION(BlueprintCallable, Category = "Fight")
	void RemoveState(const TScriptInterface<IStateSourceInterface>& source);

	UFUNCTION(BlueprintCallable, Category = "Fight")
	bool IsStateActive(int state);

	UFUNCTION(BlueprintCallable, Category = "Fight")
	void InitializeState();
};
