// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "ExtraMathPrivatePCH.h"
#include "ExtraMathBPLibrary.h"

UExtraMathBPLibrary::UExtraMathBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

bool UExtraMathBPLibrary::IsInSectorRange(FVector& SrcLocation, FRotator& Rotator, FVector& TargetLocation, float angle)
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

void UExtraMathBPLibrary::GetMaskedDirction(FVector& Start, FVector& End, FVector& Mask, FVector& Dirction)
{
	Dirction = End - Start;
	Dirction.Normalize();
	Dirction *= Mask;
}

float UExtraMathBPLibrary::GetAngle(FRotator& From, FRotator& To)
{
	return FMath::Acos(FMath::Clamp(FVector::DotProduct(From.Vector(),To.Vector()), -1.0f, 1.0f))*57.29578f;
}

void UExtraMathBPLibrary::CalculateThrowSpeed(FVector& Result, FVector& Origin, FVector& Target, float Time,float Gravity)
{
	FVector ToTarget = Target - Origin;
	float z = ToTarget.Z;
	float xy = ToTarget.Size2D();

	float V0z = z / Time + 0.5f * Gravity *Time;
	float V0xy = xy / Time;
	
	Result = ToTarget.GetSafeNormal2D();
	Result *= V0xy;
	Result.Z = V0z;
}

