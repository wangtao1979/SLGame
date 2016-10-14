// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "StrategyPawn.generated.h"

UCLASS()
class AStrategyPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AStrategyPawn();

	// Called when the game staStrategy or when spawned
	virtual void BeginPlay() override;

public:

	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* HullMesh;

	/** Camera component that will be our viewpoint */
	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStrategyCameraComponent* Camera;

	/** Spring arm that will offset the camera */
	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm;

	/** Returns Camera subobject **/
	FORCEINLINE class UStrategyCameraComponent* GetCamera() const { return Camera; }

	FORCEINLINE class USpringArmComponent* GetSpringArm() const { return SpringArm; }
};
