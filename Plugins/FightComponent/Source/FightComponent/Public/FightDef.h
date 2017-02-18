// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FightDef.generated.h"


DECLARE_LOG_CATEGORY_EXTERN(FightLog, Log, All);


//UENUM(BlueprintType)
//enum class EBuffType
//{
//	Add 	UMETA(DisplayName = "Add"),
//	Per 	UMETA(DisplayName = "Per"),
//};
USTRUCT(BlueprintType)
struct FAttributeBuff
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite)
	uint8 Type;

	UPROPERTY(BlueprintReadWrite)
	float Value;

	UPROPERTY(BlueprintReadWrite)
	bool IsPercent;

	FAttributeBuff():
		Type(0),
		Value(0.0f),
		IsPercent(false)
	{

	}
	FAttributeBuff(uint8 _Type, float _Value, bool _IsPercent):
		Type(_Type),
		Value(_Value),
		IsPercent(_IsPercent)
	{
	}
};


USTRUCT(BlueprintType)
struct FAttributeBuffConfiger
{
	GENERATED_USTRUCT_BODY()
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<float> Limit;
};


USTRUCT(BlueprintType)
struct FAttribute
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite)
	TArray<float> BuffValue;

	UPROPERTY(BlueprintReadWrite)
	TArray<float> BuffPer;

	UPROPERTY(BlueprintReadWrite)
	TArray<float> Final;

	UPROPERTY()
	int32 AttributeNumber;

	void Init(int32 _AttributeNumber)
	{
		AttributeNumber = _AttributeNumber;
		BuffValue.AddZeroed(AttributeNumber);
		BuffPer.AddZeroed(AttributeNumber);
		Final.AddZeroed(AttributeNumber);
	}

	void Clear()
	{
		for (int32 i = 0; i < AttributeNumber; i++)
		{
			BuffValue[i] = 0.0f;
		}
		for (int32 i = 0; i < AttributeNumber; i++)
		{
			BuffPer[i] = 0.0f;
		}
	}

	void Compute(TArray<float>& PerTargetAttribute)
	{
		for (int32 i = 0; i < AttributeNumber; i++)
		{
			Final[i]= PerTargetAttribute[i] * BuffPer[i] + BuffValue[i];
		}
	}
	void Count(TArray<float>& Attribute)
	{
		for (int32 i = 0; i < AttributeNumber; i++)
		{
			Attribute[i] += Final[i];
		}
	}
};