// Fill out your copyright notice in the Description page of Project Settings.

#include "SummonMaster.h"
#include "MaterialFunctionLibrary.h"



UTexture* UMaterialFunctionLibrary::GetParameterTexture(UMaterialInterface* material, FName name)
{
	UTexture* texture;
	if (material->GetTextureParameterValue(name, texture))
	{
		return texture;
	}
	else
	{
		return nullptr;
	}
}