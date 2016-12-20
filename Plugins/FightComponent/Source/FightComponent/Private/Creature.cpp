// Fill out your copyright notice in the Description page of Project Settings.

#include "FightComponentPrivatePCH.h"
#include "Creature.h"


// Sets default values
ACreature::ACreature()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	State = CreateDefaultSubobject<UCreatureStateComponent>(TEXT("State"));
	Attribute = CreateDefaultSubobject<UCreatureAttributeComponent>(TEXT("Attribute"));
}

// Called when the game starts or when spawned
void ACreature::BeginPlay()
{
	Super::BeginPlay();

	// 记录原始缩放信息
	original_scale = GetActorScale();
}

// Called every frame
void ACreature::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}


void ACreature::Scale(float scale)
{
	SetActorScale3D(original_scale*scale);
}


void ACreature::ResetScale(float scale)
{
	SetActorScale3D(original_scale);
}