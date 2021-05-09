// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Sushi.h"
#include "SushiGameStateBase.generated.h"

class ASushiList;


UCLASS()
class SUSHIGAME_API ASushiGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

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
