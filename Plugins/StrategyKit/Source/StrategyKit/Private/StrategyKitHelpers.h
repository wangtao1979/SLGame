// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.


#pragma once


class StrategyKitHelpers
{
public:
	/** convert point in screen space to ray in world space */
	static bool DeprojectScreenToWorld(const FVector2D& ScreenPosition, class ULocalPlayer* Player, FVector& RayOrigin, FVector& RayDirection);

	/** find intersection of ray in world space with ground plane */
	static FVector IntersectRayWithPlane(const FVector& RayOrigin, const FVector& RayDirection, const FPlane& Plane);
};
