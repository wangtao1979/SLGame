// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "CreatureStateComponent.h"
#include "CreatureAttributeComponent.h"
#include "UObjectGlobals.h"
#include "UObjectThreadContext.h"
#include "Creature.generated.h"

UCLASS(Blueprintable)
class ACreature : public ACharacter
{
	GENERATED_BODY()

protected:

	FVector original_scale;

	float AnimationSpeed;

public:


	UPROPERTY(Category = Creatue, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UCreatureStateComponent* State;

	UPROPERTY(Category = Creatue, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UCreatureAttributeComponent* Attribute;
public:
	// Sets default values for this character's properties
	ACreature();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;


	UFUNCTION(BlueprintCallable, Category = "Creature", meta = (AllowPrivateAccess = "true"))
	void Scale(float scale);


	UFUNCTION(BlueprintCallable, Category = "Creature", meta = (AllowPrivateAccess = "true"))
	void ResetScale(float scale);

};
