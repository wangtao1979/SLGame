// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FightDef.generated.h"


DECLARE_LOG_CATEGORY_EXTERN(FightLog, Log, All);

UENUM(BlueprintType)
enum class EBuffType
{
	Add 	UMETA(DisplayName = "Add"),
	Per 	UMETA(DisplayName = "Per"),
};

USTRUCT()
struct FAttributeVector
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(Category = Fight, VisibleAnywhere, BlueprintReadWrite)
	TArray<float> Value;

	float Get(uint8 type)
	{
		return Value[type];
	}
	float Set(uint8 type, float value)
	{
		Value[type] = value;
	}
	float Add(uint8 type, float value)
	{
		Value[type] += value;
	}
};


USTRUCT(BlueprintType)
struct FAttributeBuff
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(Category = Fight, VisibleAnywhere, BlueprintReadWrite)
	uint8 Type;

	UPROPERTY(Category = Fight, VisibleAnywhere, BlueprintReadWrite)
	float Value;
};

USTRUCT(BlueprintType)
struct FAttributeBuffContainerConfiger
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(Category = Fight, VisibleAnywhere, BlueprintReadWrite)
	uint8 Type;

	UPROPERTY(Category = Fight, VisibleAnywhere, BlueprintReadWrite)
	float Limit;


	UPROPERTY(Category = Fight, VisibleAnywhere, BlueprintReadWrite)
	TEnumAsByte<EBuffType> BuffType;

};

USTRUCT()
struct FAttributeBuffContainer
{
	GENERATED_USTRUCT_BODY()

	FAttributeBuffContainerConfiger configer;

	UPROPERTY(Category = Fight, VisibleAnywhere, BlueprintReadWrite)
	TArray<FAttributeBuff> BuffList;

	void CountBuff(FAttributeVector& vector)
	{
		for (FAttributeBuff buff : BuffList)
		{
			vector.Add(buff.Type, buff.Value);
		}
	}
};
