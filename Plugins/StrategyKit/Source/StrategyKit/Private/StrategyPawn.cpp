// Fill out your copyright notice in the Description page of Project Settings.

#include "StrategyKitPrivatePCH.h"
#include "StrategyPawn.h"
#include "StrategyController.h"
#include "StrategyCameraComponent.h"


// Sets default values
AStrategyPawn::AStrategyPawn()
{

	HullMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HullMesh"));
	RootComponent = HullMesh;
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	// Create camera component
	Camera = CreateDefaultSubobject<UStrategyCameraComponent>(TEXT("Camera"));
	Camera->AttachToComponent(SpringArm, FAttachmentTransformRules::KeepRelativeTransform, USpringArmComponent::SocketName);

	Camera->bUsePawnControlRotation = false; // Don't rotate camera with the controller

	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game staStrategy or when spawned
void AStrategyPawn::BeginPlay()
{
	Super::BeginPlay();
	auto StrategyController = Cast<AStrategyController>(GetController());
	if (StrategyController)
	{
		StrategyController->CurrentMouseCursor = StrategyController->DefaultMouseCursor;
	}
}
