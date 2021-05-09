// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Sushi.h"
#include "SushiGameStateBase.generated.h"

class ASushiList;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTurnStartedDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTurnFinishedDelegate);


UCLASS()
class SUSHIGAME_API ASushiGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		FTurnStartedDelegate TurnStartedDelegate;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		FTurnFinishedDelegate TurnFinishedDelegate;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<ASushiList*> Hands;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<ASushiList*> Plates;

public:
	ASushiGameStateBase();

	UFUNCTION(BlueprintCallable, NetMulticast, Reliable)
		void AddToHand(int _PlayerID, SushiType Sushi);

	UFUNCTION(BlueprintCallable, NetMulticast, Reliable)
		void AddToPlate(int _PlayerID, SushiType Sushi);

};
