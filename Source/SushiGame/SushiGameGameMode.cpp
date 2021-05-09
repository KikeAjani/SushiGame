// Copyright Epic Games, Inc. All Rights Reserved.

#include "SushiGameGameMode.h"
#include "SushiGameStateBase.h"
#include "SushiList.h"
#include "SushiPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "SushiPlayerController.h"


ASushiGameGameMode::ASushiGameGameMode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PlayerControllerClass = ASushiPlayerController::StaticClass();
	DefaultPawnClass = ASushiPlayer::StaticClass();

	NumSushiPlayers = 0;
}

void ASushiGameGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if (GetLocalRole() == ROLE_Authority)
	{
		ASushiPlayer* SushiPlayer = Cast<ASushiPlayer>(NewPlayer->GetPawn());
		if (SushiPlayer)
		{
			SushiPlayer->PlayerID = NumSushiPlayers;
		}
		NumSushiPlayers++;
	}
}

int ASushiGameGameMode::NumOfSushisForPlayer()
{
	return 8; //TODO
}

void ASushiGameGameMode::InitSushiGame_Implementation()
{
	ASushiGameStateBase* SushiGameState = Cast<ASushiGameStateBase>(GetWorld()->GetGameState());
	if ((GetLocalRole() == ROLE_Authority) && SushiGameState)
	{
		// Init empty Plates
		for (int i = 0; i < NumSushiPlayers; ++i)
		{
			for (int j = 0; j < NumOfSushisForPlayer(); ++j)
			{
				SushiGameState->AddToPlate(i, SushiType::MAKI); //PROVISIONAL TO TEST (SHOULD BE NONE)
			}
		}

		// Init Hands
		{
			// Init Sushis to deal
			for (int i = 0; i < NumTotalSushis; ++i)
			{
				SushisToDeal.Add(SushiType::MAKI); //TODO
			}

			// Deal (random)
			for (int i = 0; i < NumSushiPlayers; ++i)
			{
				for (int j = 0; j < NumOfSushisForPlayer(); ++j)
				{
					int RandomSushi = FMath::RandRange(0, SushisToDeal.Num() - 1);
					SushiGameState->AddToHand(i, SushisToDeal[RandomSushi]);

					SushisToDeal.RemoveAt(RandomSushi);
				}
			}
		}
	}
}

void ASushiGameGameMode::CalculatePoints_Implementation()
{
	if (GetLocalRole() == ROLE_Authority)
	{

	}
}
