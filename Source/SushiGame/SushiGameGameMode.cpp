// Copyright Epic Games, Inc. All Rights Reserved.

#include "SushiGameGameMode.h"
#include "SushiPlayer.h"
#include "SushiPlayerController.h"

ASushiGameGameMode::ASushiGameGameMode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	/* Use our custom Player-Controller Class */
	//PlayerControllerClass = ASushiPlayerController::StaticClass();
	//DefaultPawnClass = ASushiPlayer::StaticClass();
}

void ASushiGameGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	if (GetLocalRole() == ROLE_Authority){
	
	}
}

