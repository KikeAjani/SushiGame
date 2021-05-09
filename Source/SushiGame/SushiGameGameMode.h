// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once
#include "Sushi.h"
#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "SushiGameGameMode.generated.h"


UCLASS()
class SUSHIGAME_API ASushiGameGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	int NumSushiPlayers;

private:
	const int NumTotalSushis = 181;

	UPROPERTY()
		TArray<SushiType> SushisToDeal;

public:
	UFUNCTION(BlueprintCallable, Server, Reliable)
		void InitSushiGame();

	UFUNCTION(BlueprintCallable, Server, Reliable)
		void CalculatePoints();

private:
	ASushiGameGameMode(const FObjectInitializer& ObjectInitializer);

	virtual void PostLogin(APlayerController* NewPlayer) override;

	int NumOfSushisForPlayer();

};
