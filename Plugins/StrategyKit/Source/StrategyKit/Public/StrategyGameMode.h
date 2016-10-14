// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "StrategyGameMode.generated.h"

/**
 *
 */
UCLASS(config = Game)
class AStrategyGameMode : public AGameMode
{
	GENERATED_UCLASS_BODY()

	/**
	* Handle new player, skips pawn spawning.
	* @param NewPlayer
	*/
	//virtual void RestartPlayer(AController* NewPlayer) override;
public:

	UFUNCTION(BlueprintCallable, Category = "GameMode")
	void SeamlessTravel(const FString& InURL);

	UFUNCTION(BlueprintCallable, Category = "GameMode")
	bool IsInSeamlessTravel();

	UFUNCTION(BlueprintImplementableEvent)
	TArray<AActor*> ExGetSeamlessTravelActorList(bool bToEntry);


	void GetSeamlessTravelActorList(bool bToEntry, TArray<AActor*>& ActorList) override;


	/**
	* Called after a seamless level transition has been completed on the *new* GameMode.
	* Used to reinitialize players already in the game as they won't have *Login() called on them
	*/
	virtual void PostSeamlessTravel() override;


	UFUNCTION(BlueprintImplementableEvent)
	void OnSeamlessTravelFinlish();

	/** this function allows pausing the seamless travel in the middle,
	* right before it staStrategy loading the destination (i.e. while in the transition level)
	* this gives the opportunity to perform any other loading tasks before the final transition
	* this function has no effect if we have already started loading the destination (you will get a log warning if this is the case)
	* @param bNowPaused - whether the transition should now be paused
	*/
	UFUNCTION(BlueprintCallable, Category = "GameMode")
	void SetSeamlessTravelMidpointPause(bool bNowPaused);

	/** Does end of game handling for the online layer */
	//void RestartPlayer(class AController* NewPlayer) override;

	AActor* FindPlayerStart_Implementation(AController* Player, const FString& IncomingName) override;

	APawn* SpawnDefaultPawnFor_Implementation(AController* NewPlayer, AActor* StaStrategypot) override;
};

