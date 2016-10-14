// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "MaterialFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class SUMMONMASTER_API UMaterialFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "MaterialFunctionLibrary")
	static UTexture* GetParameterTexture(UMaterialInterface* material, FName name);
};
