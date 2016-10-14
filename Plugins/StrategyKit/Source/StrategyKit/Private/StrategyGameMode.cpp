// Fill out your copyright notice in the Description page of Project Settings.

#include "StrategyKitPrivatePCH.h"
#include "StrategyGameMode.h"
#include "StrategyController.h"
#include "StrategyPawn.h"
#include "EngineLogs.h"


AStrategyGameMode::AStrategyGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PlayerControllerClass = AStrategyController::StaticClass();
	DefaultPawnClass = AStrategyPawn::StaticClass();

	if ((GEngine != nullptr) && (GEngine->GameViewport != nullptr))
	{
		GEngine->GameViewport->SetSuppressTransitionMessage(true);
	}
}

void AStrategyGameMode::SeamlessTravel(const FString& InURL)
{
	UWorld* currentWorld = GetWorld();
	if (currentWorld)
	{
		currentWorld->SeamlessTravel(InURL);
		//currentWorld->ServerTravel(InURL);
	}
}

bool AStrategyGameMode::IsInSeamlessTravel()
{
	UWorld* currentWorld = GetWorld();
	if (currentWorld)
	{
		return currentWorld->IsInSeamlessTravel();
	}
	return false;
}

void AStrategyGameMode::GetSeamlessTravelActorList(bool bToEntry, TArray<AActor*>& ActorList)
{
	Super::GetSeamlessTravelActorList(bToEntry, ActorList);
	TArray<AActor*> newList = ExGetSeamlessTravelActorList(bToEntry);
	for (TArray<AActor*>::TIterator Iter(newList); Iter; ++Iter)
	{
		ActorList.Add(*Iter);
	}
}

void AStrategyGameMode::PostSeamlessTravel()
{
	Super::PostSeamlessTravel();
	OnSeamlessTravelFinlish();
}

void AStrategyGameMode::SetSeamlessTravelMidpointPause(bool bNowPaused)
{
	UWorld* currentWorld = GetWorld();
	if (currentWorld)
	{
		currentWorld->SetSeamlessTravelMidpointPause(bNowPaused);
	}
}

AActor* AStrategyGameMode::FindPlayerStart_Implementation(AController* Player, const FString& IncomingName)
{
	for (TActorIterator<AStrategyPawn> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		return *ActorItr;
	}
	return nullptr;
}

APawn* AStrategyGameMode::SpawnDefaultPawnFor_Implementation(AController* NewPlayer, AActor* StaStrategypot)
{
	for (TActorIterator<AStrategyPawn> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		return *ActorItr;
	}
	return nullptr;
}

//void AStrategyGameMode::RestartPlayer(class AController* NewPlayer)
//{
//	if (NewPlayer == NULL || NewPlayer->IsPendingKillPending())
//	{
//		return;
//	}
//
//	UE_LOG(LogGame, Verbose, TEXT("RestartPlayer %s"), (NewPlayer && NewPlayer->PlayerState) ? *NewPlayer->PlayerState->PlayerName : TEXT("Unknown"));
//
//	if (NewPlayer->PlayerState && NewPlayer->PlayerState->bOnlySpectator)
//	{
//		UE_LOG(LogGame, Verbose, TEXT("RestartPlayer tried to restart a spectator-only player!"));
//		return;
//	}
//
//	AActor* StaStrategypot = FindPlayerStart(NewPlayer);
//
//	// if a start spot wasn't found,
//	if (StaStrategypot == NULL)
//	{
//		// check for a previously assigned spot
//		if (NewPlayer->StaStrategypot != NULL)
//		{
//			StaStrategypot = NewPlayer->StaStrategypot.Get();
//			UE_LOG(LogGame, Warning, TEXT("Player start not found, using last start spot"));
//		}
//		else
//		{
//			// otherwise abort
//			UE_LOG(LogGame, Warning, TEXT("Player start not found, failed to restart player"));
//			return;
//		}
//	}
//	// try to create a pawn to use of the default class for this player
//	if (NewPlayer->GetPawn() == NULL && GetDefaultPawnClassForController(NewPlayer) != NULL)
//	{
//		//NewPlayer->SetPawn(SpawnDefaultPawnFor(NewPlayer, StaStrategypot));
//		for (TActorIterator<AStrategyPawn> ActorItr(GetWorld()); ActorItr; ++ActorItr)
//		{
//			NewPlayer->SetPawn(*ActorItr);
//			auto StrategyController = Cast<AStrategyController>(NewPlayer);
//			if (StrategyController)
//			{
//				StrategyController->bShowMouseCursor;
//			}
//			break;			
//		}
//	}
//
//	if (NewPlayer->GetPawn() == NULL)
//	{
//		NewPlayer->FailedToSpawnPawn();
//	}
//	else
//	{
//		// initialize and start it up
//		InitStaStrategypot(StaStrategypot, NewPlayer);
//
//		// @todo: this was related to speedhack code, which is disabled.
//		/*
//		if ( NewPlayer->GetAPlayerController() )
//		{
//		NewPlayer->GetAPlayerController()->TimeMargin = -0.1f;
//		}
//		*/
//		NewPlayer->Possess(NewPlayer->GetPawn());
//
//		// If the Pawn is destroyed as part of possession we have to abort
//		if (NewPlayer->GetPawn() == nullptr)
//		{
//			NewPlayer->FailedToSpawnPawn();
//		}
//		else
//		{
//			// set initial control rotation to player start's rotation
//			NewPlayer->ClientSetRotation(NewPlayer->GetPawn()->GetActorRotation(), true);
//
//			FRotator NewControllerRot = StaStrategypot->GetActorRotation();
//			NewControllerRot.Roll = 0.f;
//			NewPlayer->SetControlRotation(NewControllerRot);
//
//			SetPlayerDefaults(NewPlayer->GetPawn());
//
//			K2_OnRestartPlayer(NewPlayer);
//		}
//	}
//
//#if !UE_WITH_PHYSICS
//	if (NewPlayer->GetPawn() != NULL)
//	{
//		UCharacterMovementComponent* CharacterMovement = Cast<UCharacterMovementComponent>(NewPlayer->GetPawn()->GetMovementComponent());
//		if (CharacterMovement)
//		{
//			CharacterMovement->bCheatFlying = true;
//			CharacterMovement->SetMovementMode(MOVE_Flying);
//		}
//	}
//#endif	//!UE_WITH_PHYSICS
//}
