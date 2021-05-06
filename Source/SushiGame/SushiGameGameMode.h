// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once
#include "SushiPlayer.h"
#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "SushiGameGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SUSHIGAME_API ASushiGameGameMode : public AGameMode
{
	GENERATED_BODY()

		ASushiGameGameMode(const FObjectInitializer& ObjectInitializer);

	virtual void PostLogin(APlayerController* NewPlayer) override;

};
