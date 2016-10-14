// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "StrategyKitPrivatePCH.h"
#include "StrategyKitHelpers.h"

bool StrategyKitHelpers::DeprojectScreenToWorld(const FVector2D& ScreenPosition, ULocalPlayer* Player, FVector& RayOrigin, FVector& RayDirection)
{
	if (Player != NULL && Player->ViewportClient != NULL && Player->ViewportClient->Viewport != NULL && Player->PlayerController != NULL)
	{
		//get the projection data
		FSceneViewProjectionData ProjectionData;
		if (Player->GetProjectionData(Player->ViewportClient->Viewport, eSSP_FULL, /*out*/ ProjectionData))
		{
			const FMatrix ViewMatrix = FTranslationMatrix(-ProjectionData.ViewOrigin) * ProjectionData.ViewRotationMatrix;
			const FMatrix InvViewMatrix = ViewMatrix.InverseFast();
			const FMatrix InvProjectionMatrix = ProjectionData.ProjectionMatrix.InverseFast();

			FSceneView::DeprojectScreenToWorld(ScreenPosition, ProjectionData.GetConstrainedViewRect(), InvViewMatrix, InvProjectionMatrix, /*out*/ RayOrigin, /*out*/ RayDirection);

			return true;
		}
	}

	return false;
}

FVector StrategyKitHelpers::IntersectRayWithPlane(const FVector& RayOrigin, const FVector& RayDirection, const FPlane& Plane)
{
	const FVector PlaneNormal = FVector(Plane.X, Plane.Y, Plane.Z);
	const FVector PlaneOrigin = PlaneNormal * Plane.W;

	const float Distance = FVector::DotProduct((PlaneOrigin - RayOrigin), PlaneNormal) / FVector::DotProduct(RayDirection, PlaneNormal);
	return RayOrigin + RayDirection * Distance;
}
