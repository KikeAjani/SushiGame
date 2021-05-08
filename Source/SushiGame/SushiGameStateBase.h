// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "SushiGameStateBase.generated.h"

/**
 * 
 */


class ASushi;
class ASushiPlayer;
USTRUCT()
struct FHand
{
	GENERATED_USTRUCT_BODY()

		// Item class to spawn
		UPROPERTY()
		TArray<ASushi*> Sushis;
};

UCLASS()
class SUSHIGAME_API ASushiGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

	TArray<FHand*> Hands;
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<FHand> Plates;
	UFUNCTION()
		void CalculatePoints();
	
};
