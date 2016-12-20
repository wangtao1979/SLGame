// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "ExtraMathPrivatePCH.h"
#include "ExtraMathBPLibrary.h"

UExtraMathBPLibrary::UExtraMathBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

bool UExtraMathBPLibrary::IsInSectorRange(FVector SrcLocation, FRotator Rotator, FVector TargetLocation, float angle)
{
	SrcLocation.Z = 0.0f;
	TargetLocation.Z = 0.0f;
	FVector Dir = TargetLocation - SrcLocation;
	Dir.Normalize();
	FVector SrcDir = Rotator.Vector();
	float delta1 = FVector::DotProduct(SrcDir, Dir);
	float delta2 = FMath::Cos(FMath::DegreesToRadians(angle*0.5));
	return delta1 > delta2;
}

